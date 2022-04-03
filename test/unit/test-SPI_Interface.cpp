#include <gtest/gtest.h>
#include <fcntl.h>
#include <pthread.h>

#include "IO/MessageHandler.h"
#include "broker/broker.h"
#include "IO/SPI.h"
#include "IO/SPI_UserOperations.h"

using namespace IO;

void queueMessageToInterfaceRX(IOInterface* obj, msg::GENERIC_MESSAGE* m);

void init_func(int fileDescriptor, IOInterface* obj)
{
    static msg::raw::TEST_MESSAGE_READ m;
    m.VAR1 = 10;
    m.VAR2 = 10;
    m.size = msg::RAW_MESSAGE_SIZES[msg::id::TEST_MESSAGE_READ];
    m.id = msg::id::TEST_MESSAGE_READ;
    queueMessageToInterfaceRX(obj, &m);
}

TEST(SPIInterfaceTest, InitFunction)
{
    using namespace pubsub;
    Subscriber<msg::real::TEST_MESSAGE_READ>* sub = (Subscriber<msg::real::TEST_MESSAGE_READ>*)generateSubscriber(msg::id::TEST_MESSAGE_READ);
    MessageHandler handler;
    SPI_Interface temp_spi;

    // Create temporary device file
    close(open("device.temp", O_RDWR|O_CREAT));

    // Setup Interface
    defaultMessageHandlerSetup(handler);
    handler.attachIOInterface(&temp_spi);
    temp_spi.registerDevice("device", "device.temp");
    temp_spi.registerInitFunction("device", init_func);

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

pthread_cond_t spi_periodic_data_ready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t spi_periodic_data_mtx = PTHREAD_MUTEX_INITIALIZER;
void periodic_func(int fileDescriptor, IOInterface* obj)
{
    static msg::raw::TEST_MESSAGE_READ m;
    m.VAR1 = 10;
    m.VAR2 = 10;
    m.size = msg::RAW_MESSAGE_SIZES[msg::id::TEST_MESSAGE_READ];
    m.id = msg::id::TEST_MESSAGE_READ;
    queueMessageToInterfaceRX(obj, &m);
    pthread_cond_signal(&spi_periodic_data_ready);
}

TEST(SPIInterfaceTest, PeriodicFunction)
{
    using namespace pubsub;
    Subscriber<msg::real::TEST_MESSAGE_READ>* sub = (Subscriber<msg::real::TEST_MESSAGE_READ>*)generateSubscriber(msg::id::TEST_MESSAGE_READ);
    MessageHandler handler;
    SPI_Interface temp_spi;

    // Create temporary device file
    close(open("device.temp", O_RDWR|O_CREAT));

    // Setup Interface
    defaultMessageHandlerSetup(handler);
    handler.attachIOInterface(&temp_spi);
    temp_spi.registerDevice("device", "device.temp");
    temp_spi.registerOperation("device", SPI_READ, msg::id::TEST_MESSAGE_READ, 50, periodic_func);

    // Test Execution
    pthread_cond_wait(&spi_periodic_data_ready, &spi_periodic_data_mtx);
    usleep(1000);
    EXPECT_TRUE(sub->isDataAvailable()) << "First";
    EXPECT_EQ(sub->getDataRef()->VAR1, 10);

    pthread_cond_wait(&spi_periodic_data_ready, &spi_periodic_data_mtx);
    usleep(1000);
    EXPECT_TRUE(sub->isDataAvailable()) << "Second";
    EXPECT_EQ(sub->getDataRef()->VAR1, 10);

    // Cleanup
    remove("device.temp");
    sub->unsubscribe();
}

bool spi_write_func_executed = false;
pthread_cond_t spi_write_data_ready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t spi_write_data_mtx = PTHREAD_MUTEX_INITIALIZER;
void write_func(int fileDescriptor, IOInterface* obj)
{
    spi_write_func_executed = true;
    pthread_cond_signal(&spi_write_data_ready);
}

TEST(SPIInterfaceTest, WriteFunction)
{
    using namespace pubsub;
    Publisher<msg::real::TEST_MESSAGE_WRITE>* pub = (Publisher<msg::real::TEST_MESSAGE_WRITE>*)generatePublisher(msg::id::TEST_MESSAGE_WRITE);
    MessageHandler handler;
    SPI_Interface temp_spi; 

    // Create temporary device file
    close(open("device.temp", O_RDWR|O_CREAT));

    // Setup Interface
    defaultMessageHandlerSetup(handler);
    handler.attachIOInterface(&temp_spi);
    temp_spi.registerDevice("device", "device.temp");
    temp_spi.registerOperation("device", SPI_WRITE, msg::id::TEST_MESSAGE_WRITE, 50, write_func);

    // Execution
    msg::real::TEST_MESSAGE_WRITE msg;
    pub->publish(&msg);
    pthread_cond_wait(&spi_write_data_ready, &spi_write_data_mtx);
    EXPECT_TRUE(spi_write_func_executed);

    // Cleanup
    remove("device.temp");
}