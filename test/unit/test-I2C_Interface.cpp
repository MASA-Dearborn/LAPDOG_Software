#include <gtest/gtest.h>
#include <fcntl.h>
#include "IO/MessageHandler.h"
#include "broker/broker.h"
#include "IO/I2C.h"
#include "IO/I2C_UserOperations.h"

using namespace IO;

void init_func(int fileDescriptor, int slave_address, msg::GENERIC_MESSAGE* msg)
{

}

TEST(I2CInterfaceTest, InitFunction)
{
    pubsub::Subscriber<msg::real::ALTIMETER_COEFFS>* sub = createNewSubscriber(ALTIMETER_COEFFS);
    MessageHandler handler;
    I2C_Interface temp_i2c;

    // Create temporary device file
    close(open("device.temp", O_RDWR|O_CREAT));

    // Setup Interface
    temp_i2c.registerDevice("device", "device.temp", 0x50);
    temp_i2c.registerInitFunction("device", i2c_operations::ALTIMETER_READ_CONFIG);
    handler.attachIOInterface(&temp_i2c);

    // Wait for handler to get message
    sched_yield();
    usleep(5000);

    // Read back message
    EXPECT_TRUE(sub->isDataAvailable());

    // Cleanup
    remove("device.temp");
    sub->unsubscribe();
}