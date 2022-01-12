#include "IO/MessageHandler.h"

#define __ADD_PUBLISHER_TO_MESSAGE_HANDLER(name)     publishers[msg::id::name] = createNewPublisher(name)
#define __ADD_SUBSCRIBER_TO_MESSAGE_HANDLER(name)    subscribers[msg::id::name] = createNewSubscriber(name)

MessageHandler::MessageHandler()
{
    _initPublishers();
    _initSubscribers();
    messageHandlerThread = std::thread(&MessageHandler::_threadProcess, this);
}

MessageHandler::~MessageHandler()
{

}

void MessageHandler::attachIOInterface(IO::IOInterface* interface)
{
    IOInterfaceList[interface->getType()].push_back(interface);
}

void MessageHandler::publishMessageToBroker(msg::GENERIC_MESSAGE* message)
{
    if (message == nullptr) 
        return;

    publishers[message->id]->publish(message);
}

void MessageHandler::sendSubscribedToIO(msg::GENERIC_MESSAGE* message)
{   
    if (message == nullptr) 
        return;

    for(std::vector<IO::IOInterface*> IOInterfaceVector : IOInterfaceList)
    {
        for(auto& IOInterface : IOInterfaceVector)
        {
            IOInterface->writeMessage((uint8_t*)message, message->size);
        }
    }
}

/**
 * @brief   Initializes the IO publishers required by the MessageHandler
 * 
 */
void MessageHandler::_initPublishers()
{
    __ADD_PUBLISHER_TO_MESSAGE_HANDLER(TEST_MESSAGE);
}

void MessageHandler::_initSubscribers()
{
    __ADD_SUBSCRIBER_TO_MESSAGE_HANDLER(TEST_MESSAGE_2);
}
