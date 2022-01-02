#include "IO/IOInterface.h"

using namespace IO;

int IOInterface::getMessageSize() 
{ 
    if ((msg::GENERIC_MESSAGE*)RX_BUFFER.peak() == nullptr) 
        return -1;
    else
        return ((msg::GENERIC_MESSAGE*)RX_BUFFER.peak())->size; 
}

int IOInterface::getMessageID() 
{ 
    if ((msg::GENERIC_MESSAGE*)RX_BUFFER.peak() == nullptr) 
        return -1;
    else
        return ((msg::GENERIC_MESSAGE*)RX_BUFFER.peak())->id; 
}