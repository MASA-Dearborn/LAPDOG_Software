#include "IO/IOInterface.h"

using namespace IO;

int IOInterface::getMessageSize() 
{ 
    if ((msg::GENERIC_MESSAGE*)RX_BUFFER_PTR.get()->peek() == nullptr) 
        return -1;
    else
        return ((msg::GENERIC_MESSAGE*)(RX_BUFFER_PTR.get()->peek()))->size; 
}

int IOInterface::getMessageID() 
{ 
    if ((msg::GENERIC_MESSAGE*)(RX_BUFFER_PTR.get()->peek()) == nullptr) 
        return -1;
    else
        return ((msg::GENERIC_MESSAGE*)RX_BUFFER_PTR.get()->peek())->id; 
}

/**
 * @brief   Initialize StaticBuffers on the heap
 * 
 * @return  int -1 for failure and 1 for success
 */
int IOInterface::initBuffers()
{
    RX_BUFFER_PTR = std::unique_ptr<StaticQueue<uint8_t, BUFFER_SIZE>>(new StaticQueue<uint8_t, BUFFER_SIZE>());
    TX_BUFFER_PTR = std::unique_ptr<StaticQueue<uint8_t, BUFFER_SIZE>>(new StaticQueue<uint8_t, BUFFER_SIZE>());

    if (RX_BUFFER_PTR.get() == nullptr || TX_BUFFER_PTR.get() == nullptr)
        return -1;
    return 1;
}