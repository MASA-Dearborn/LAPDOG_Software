#include "IO/MessageHandler.h"
#include "broker/broker.h"
#include "IO/I2C.h"
#include "IO/I2C_UserOperations.h"

#include <unistd.h>
#include <cstdio>

using namespace IO;

int main()
{
    char string_buf[1024];
    MessageHandler handler;
    I2C_Interface temp_i2c;

    temp_i2c.registerDevice("device", "/dev/i2c-0", 0x50);
    temp_i2c.registerInitFunction("device", i2c_operations::ALTIMETER_READ_CONFIG);
    temp_i2c.registerOperation("device", I2C_READ, msg::id::ALTIMETER_COEFFS, 500, i2c_operations::ALTIMETER_READ_CONFIG);
    handler.attachIOInterface(&temp_i2c);

    pubsub::Subscriber<msg::real::ALTIMETER_COEFFS>* sub = createNewSubscriber(ALTIMETER_COEFFS);
    msg::real::ALTIMETER_COEFFS* msg_ptr;
    while(true)
    {
        usleep(1000000);
        if (sub->isDataAvailable())
        {
            msg::conv::stringifyRealMessage(string_buf, (msg::GENERIC_MESSAGE*)sub->getData());
            printf("%s", string_buf);
        }
    }

}