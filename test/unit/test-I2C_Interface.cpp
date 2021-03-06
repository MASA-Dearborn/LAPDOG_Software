#include <gtest/gtest.h>
#include <fcntl.h>
#include <pthread.h>

#include "IO/MessageHandler.h"
#include "broker/broker.h"
#include "IO/I2C.h"
#include "IO/I2C_UserOperations.h"

using namespace IO;

void queueMessageToInterfaceRX(IOInterface* obj, msg::GENERIC_MESSAGE* m)
{
    obj->getRXBuffer()->enqueue((uint8_t*)m, m->size);
}

void init_func(int fileDescriptor, int slave_address, IOInterface* obj)
{
    static msg::raw::TEST_MESSAGE_READ m;
    m.VAR1 = 10;
    m.VAR2 = 10;
    m.size = msg::RAW_MESSAGE_SIZES[msg::id::TEST_MESSAGE_READ];
    m.id = msg::id::TEST_MESSAGE_READ;
    queueMessageToInterfaceRX(obj, &m);
}

TEST(I2CInterfaceTest, InitFunction)
{
    using namespace pubsub;
    Subscriber<msg::real::TEST_MESSAGE_READ>* sub = (Subscriber<msg::real::TEST_MESSAGE_READ>*)generateSubscriber(msg::id::TEST_MESSAGE_READ);
    MessageHandler handler;
    I2C_Interface temp_i2c;

    // Create temporary device file
    close(open("device.temp", O_RDWR|O_CREAT));

    // Setup Interface
    defaultMessageHandlerSetup(handler);
    handler.attachIOInterface(&temp_i2c);
    temp_i2c.registerDevice("device", "device.temp", 0x50);
    temp_i2c.registerInitFunction("device", init_func);

    // Wait for handler to get message
    sched_yield();
    usleep(50000);

    // Read back message
    EXPECT_TRUE(sub->isDataAvailable());
    EXPECT_EQ(sub->getDataRef()->VAR1, 10);

    // Cleanup
    remove("device.temp");
    sub->unsubscribe();
}

pthread_cond_t i2c_periodic_data_ready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t i2c_periodic_data_mtx = PTHREAD_MUTEX_INITIALIZER;
void periodic_func(int fileDescriptor, int slave_address, IOInterface* obj)
{
    static msg::raw::TEST_MESSAGE_READ m;
    m.VAR1 = 10;
    m.VAR2 = 10;
    m.size = msg::RAW_MESSAGE_SIZES[msg::id::TEST_MESSAGE_READ];
    m.id = msg::id::TEST_MESSAGE_READ;
    queueMessageToInterfaceRX(obj, &m);
    pthread_cond_signal(&i2c_periodic_data_ready);
}

TEST(I2CInterfaceTest, PeriodicFunction)
{
    using namespace pubsub;
    Subscriber<msg::real::TEST_MESSAGE_READ>* sub = (Subscriber<msg::real::TEST_MESSAGE_READ>*)generateSubscriber(msg::id::TEST_MESSAGE_READ);
    MessageHandler handler;
    I2C_Interface temp_i2c;

    // Create temporary device file
    close(open("device.temp", O_RDWR|O_CREAT));

    // Setup Interface
    defaultMessageHandlerSetup(handler);
    handler.attachIOInterface(&temp_i2c);
    temp_i2c.registerDevice("device", "device.temp", 0x50);
    temp_i2c.registerOperation("device", I2C_READ, msg::id::TEST_MESSAGE_READ, 50, periodic_func);

    // Test Execution
    pthread_cond_wait(&i2c_periodic_data_ready, &i2c_periodic_data_mtx);
    usleep(1000);
    EXPECT_TRUE(sub->isDataAvailable()) << "First";
    EXPECT_EQ(sub->getDataRef()->VAR1, 10);

    pthread_cond_wait(&i2c_periodic_data_ready, &i2c_periodic_data_mtx);
    usleep(1000);
    EXPECT_TRUE(sub->isDataAvailable()) << "Second";
    EXPECT_EQ(sub->getDataRef()->VAR1, 10);

    // Cleanup
    remove("device.temp");
    sub->unsubscribe();
}

bool i2c_write_func_executed = false;
pthread_cond_t i2c_write_data_ready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t i2c_write_data_mtx = PTHREAD_MUTEX_INITIALIZER;
void write_func(int fileDescriptor, int slave_address, IOInterface* obj)
{
    i2c_write_func_executed = true;
    pthread_cond_signal(&i2c_write_data_ready);
}

TEST(I2CInterfaceTest, WriteFunction)
{
    using namespace pubsub;
    Publisher<msg::real::TEST_MESSAGE_WRITE>* pub = (Publisher<msg::real::TEST_MESSAGE_WRITE>*)generatePublisher(msg::id::TEST_MESSAGE_WRITE);
    MessageHandler handler;
    I2C_Interface temp_i2c; 

    // Create temporary device file
    close(open("device.temp", O_RDWR|O_CREAT));

    // Setup Interface
    defaultMessageHandlerSetup(handler);
    handler.attachIOInterface(&temp_i2c);
    temp_i2c.registerDevice("device", "device.temp", 0x50);
    temp_i2c.registerOperation("device", I2C_WRITE, msg::id::TEST_MESSAGE_WRITE, 50, write_func);

    // Execution
    msg::real::TEST_MESSAGE_WRITE msg;
    pub->publish(&msg);
    pthread_cond_wait(&i2c_write_data_ready, &i2c_write_data_mtx);
    EXPECT_TRUE(i2c_write_func_executed);

    // Cleanup
    remove("device.temp");
}