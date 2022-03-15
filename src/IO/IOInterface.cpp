#include "IO/IOInterface.h"

using namespace IO;

int IOInterface::getMessageSize() 
{ 
    if (getMessagePtr() == nullptr) 
        return -1;
    
    int messageSize = (getMessagePtr())->size;
    int messageID = (getMessagePtr())->id;
    return (messageID < 0 || messageID >= msg::id::META_NUM_MESSAGES) ? -1 : messageSize;
}

int IOInterface::getMessageID() 
{ 
    if (getMessagePtr() == nullptr) 
        return -1;

    int messageID = (getMessagePtr())->id;
    return (messageID < 0 || messageID >= msg::id::META_NUM_MESSAGES) ? -1 : messageID;
}

bool IOInterface::isMessageAvailable()
{   
    if (getMessagePtr() == nullptr) 
        return -1;

    int messageID = (getMessagePtr())->id;
    int messageSize = getMessagePtr()->size;
    return ((messageID < 0 || messageID >= msg::id::META_NUM_MESSAGES) || messageSize <= 0) ? false : true;
}

msg::GENERIC_MESSAGE* IOInterface::getMessagePtr()
{
    msg::GENERIC_MESSAGE* message  = (msg::GENERIC_MESSAGE*)RX_BUFFER_PTR.get()->peek();
    if (message != nullptr)
        return message;
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