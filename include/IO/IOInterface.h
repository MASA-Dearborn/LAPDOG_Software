#pragma once

#include <cstdint>
#include <memory>

#include "../StaticQueue.h"
#include "../messageTypes.h"

#define BUFFER_SIZE 1024*4

namespace IO
{

    enum IOInterfaceType
    {
        TYPE_UNDEFINED = 0,
        TYPE_TCP = 1,
        TYPE_I2C,
        TYPE_SPI,
        TYPE_CAN,
        TYPE_UART,
        TYPE_GENERIC,
        NUM_TYPES,
    };

    // Virtual interface class
    class IOInterface
    {
    public:

        ~IOInterface() { isValid = false; }
        IOInterface();
        IOInterface(IOInterfaceType type);

        // IO Interaction Methods
        virtual int readMessage(uint8_t* dest, const int num) = 0;
        virtual int writeMessage(uint8_t* src, const int num) = 0;

        // RX Internal State Methods
        int getMessageSize();
        int getMessageID();
        bool isMessageAvailable();
        msg::GENERIC_MESSAGE* getMessagePtr();
        IOInterfaceType getType() { return type; }
        bool isInterfaceValid() { return isValid; };
        StaticQueue<uint8_t, BUFFER_SIZE>* getRXBuffer() { return RX_BUFFER_PTR.get(); }
        StaticQueue<uint8_t, BUFFER_SIZE>* getTXBuffer() { return TX_BUFFER_PTR.get(); }

    protected:
        int initBuffers();

        bool isValid = true;
        const IOInterfaceType type;
        std::unique_ptr<StaticQueue<uint8_t, BUFFER_SIZE>> RX_BUFFER_PTR;
        std::unique_ptr<StaticQueue<uint8_t, BUFFER_SIZE>> TX_BUFFER_PTR;

    };

    class GenericInterface : public IOInterface
    {
        public:
            GenericInterface() : IOInterface(TYPE_GENERIC) { initBuffers(); }

            int readMessage(uint8_t* dest, const int num) { return RX_BUFFER_PTR.get()->dequeue(dest, num); }
            int writeMessage(uint8_t* src, const int num) { return TX_BUFFER_PTR.get()->enqueue(src, num); }
    
    };

}