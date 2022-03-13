#include <gtest/gtest.h>
#include <fcntl.h>
#include "IO/MessageHandler.h"
#include "broker/broker.h"
#include "IO/I2C.h"
#include "IO/I2C_UserOperations.h"

using namespace IO;

void init_func(int fileDescriptor, int slave_address, msg::GENERIC_MESSAGE* msg)
{
    msg::raw::ALTIMETER_COEFFS* m = (msg::raw::ALTIMETER_COEFFS*)msg;
    m->coeff_1 = 1;
    m->coeff_2 = 2;
    m->coeff_3 = 3;
    m->coeff_4 = 4;
    m->coeff_5 = 5;
    m->coeff_6 = 6;
    m->size = msg::RAW_MESSAGE_SIZES[msg::id::ALTIMETER_COEFFS];
    m->id = msg::id::ALTIMETER_COEFFS;
}

TEST(I2CInterfaceTest, InitFunction)
{
    using namespace pubsub;

    Subscriber<msg::real::ALTIMETER_COEFFS>* sub = (Subscriber<msg::real::ALTIMETER_COEFFS>*)generateSubscriber(msg::id::ALTIMETER_COEFFS);
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
    usleep(5000);

    // Read back message
    EXPECT_TRUE(sub->isDataAvailable());

    // Cleanup
    remove("device.temp");
    sub->unsubscribe();
}