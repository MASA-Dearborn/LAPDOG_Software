#pragma once

#include <cstdint>

#include "../StaticQueue.h"
#include "../messageTypes.h"

#define BUFFER_SIZE 1024*1024*16

namespace IO
{

    // Pure Virtual interface class
    class IOInterface
    {
    public:

        // IO Interaction Methods
        virtual int readMessage(void* dest, const int num) = 0;
        virtual int writeMessage(void* src, const int num) = 0;

        // Internal State Methods
        int getMessageSize();
        int getMessageID();

    protected:
        StaticQueue<uint8_t, BUFFER_SIZE> RX_BUFFER;
        StaticQueue<uint8_t, BUFFER_SIZE> TX_BUFFER;

    };

}