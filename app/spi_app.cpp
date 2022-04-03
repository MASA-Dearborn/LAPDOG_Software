#include "messageTypes.h"
#include "IO/MessageHandler.h"
#include "broker/broker.h"
#include "IO/SPI.h"
#include "IO/SPI_Operations.h"

#include <unistd.h>
#include <cstdio>

using namespace IO;

void dequeueMessageFromInterface(IO::IOInterface* obj, msg::GENERIC_MESSAGE* dest)
{
    if (obj == nullptr || dest == nullptr)
        return;

    printf("Dequeue... ");
    int size = ((msg::GENERIC_MESSAGE*)obj->getTXBuffer()->peek())->size;
    if (dest->size >= size)
        obj->getTXBuffer()->dequeue((uint8_t*)dest, size);
}

void function(int fileDescriptor, IO::IOInterface* obj)
{
    msg::raw::TEST_MESSAGE_WRITE msg;
    char data[2] = {0x55, 0x55};
    dequeueMessageFromInterface(obj, &msg);
    _spi_half_write(fileDescriptor, data, 2);
    printf("Write done: %d\n", obj->getTXBuffer()->getDataSize());
}

int main()
{
    char string_buf[1024];
    MessageHandler handler;
    SPI_Interface temp_spi;
    msg::raw::TEST_MESSAGE_WRITE msg;
    msg.VAR1 = 0x08;
    msg.VAR2 = 0x04;

    temp_spi.registerDevice("device", "/dev/spidev1.1");
    temp_spi.registerOperation("device", SPI_WRITE, msg::id::TEST_MESSAGE_WRITE, 500, function);
    handler.attachIOInterface(&temp_spi);

    while(true)
    {
        usleep(1000000);
        temp_spi.writeMessage((uint8_t*)&msg, msg.size);
    }

}