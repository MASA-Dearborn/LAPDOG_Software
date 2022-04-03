#include "messageTypes.h"
#include "IO/MessageHandler.h"
#include "broker/broker.h"
#include "IO/CAN.h"
#include "datalogger/dataLogger.h"

#include <unistd.h>
#include <cstdio>

using namespace IO;

int main()
{
    char string_buf[1024];
    pubsub::GenericPublisher* pub = pubsub::generatePublisher(msg::id::TEST_MESSAGE_WRITE);

    DataLogger logger;
    MessageHandler handler;
    CAN_Interface temp_can;
    
    /* Init Messages */
    msg::real::TEST_MESSAGE_WRITE msg;
    msg.VAR1 = 0xFF;
    msg.VAR2 = 0.0f;

    msg::raw::TEST_MESSAGE_READ recv;
    recv.VAR1 = 0x55;
    recv.VAR2 = 0xFF;

    /* Setup Objects */
    handler.attachIOInterface(&temp_can);
    defaultMessageHandlerSetup(handler);

    while(true)
    {
        usleep(1000000);
        pub->publish(&msg);
        temp_can.getRXBuffer()->enqueue((uint8_t*)&recv, sizeof(msg::raw::TEST_MESSAGE_READ));
    }

}
