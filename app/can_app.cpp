#include "messageTypes.h"
#include "IO/MessageHandler.h"
#include "broker/broker.h"
#include "IO/CAN.h"

#include <unistd.h>
#include <cstdio>

using namespace IO;

int main()
{
    char string_buf[1024];
    MessageHandler handler;
    CAN_Interface temp_can;
    msg::raw::TEST_MESSAGE_WRITE msg;
    msg.VAR1 = 0xFF;
    msg.VAR2 = 0x55;

    handler.attachIOInterface(&temp_can);

    while(true)
    {
        usleep(1000000);
        temp_can.writeMessage((uint8_t*)&msg, msg.size);
        printf("Data Ready: %d\n", temp_can.getTXBuffer()->getDataSize());
    }

}
