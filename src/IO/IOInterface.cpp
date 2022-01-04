#include "IO/IOInterface.h"

using namespace IO;

int IOInterface::getMessageSize() 
{ 
    if ((msg::GENERIC_MESSAGE*)RX_BUFFER->peek() == nullptr) 
        return -1;
    else
        return ((msg::GENERIC_MESSAGE*)(RX_BUFFER->peek()))->size; 
}

int IOInterface::getMessageID() 
{ 
    if ((msg::GENERIC_MESSAGE*)(RX_BUFFER->peek()) == nullptr) 
        return -1;
    else
        return ((msg::GENERIC_MESSAGE*)RX_BUFFER->peek())->id; 
}

/**
 * @brief   Initialize StaticBuffers on the heap
 * 
 * @return  int -1 for failure and 1 for success
 */
int IOInterface::initBuffers()
{
    RX_BUFFER = new StaticQueue<uint8_t, BUFFER_SIZE>();
    TX_BUFFER = new StaticQueue<uint8_t, BUFFER_SIZE>();

    if (RX_BUFFER == nullptr || TX_BUFFER == nullptr)
        return -1;
    return 1;
}