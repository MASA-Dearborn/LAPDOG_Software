#include "IO/MessageHandler.h"
#include "IO/TCP.h"

#include <unistd.h>

#define __ADD_PUBLISHER_TO_MESSAGE_HANDLER(name)     publishers[msg::id::name] = createNewPublisher(name)
#define __ADD_SUBSCRIBER_TO_MESSAGE_HANDLER(name)    subscribers[msg::id::name] = createNewSubscriber(name)

MessageHandler::MessageHandler()
{
    _initPublishers();
    _initSubscribers();
    _initIOInterface();
    messageHandlerThreadObj = std::thread(&MessageHandler::_messageHandlerThread, this);
}

MessageHandler::~MessageHandler()
{

    messageHandlerThreadActive = false;
    messageHandlerThreadObj.join();

    for(std::vector<IO::IOInterface*> IOInterfaceVector : IOInterfaceList)
    {
        for(IO::IOInterface* IOInterface : IOInterfaceVector)
        {
            delete IOInterface;
        }
    }
}

/**
 * @brief   Attaches a IOInterface to the MessageHandler
 * @note    Called internally by _initIOInterface
 * 
 * @param interface Pointer to the IOInterface 
 */
void MessageHandler::attachIOInterface(IO::IOInterface* interface)
{
    IOInterfaceList[interface->getType()].push_back(interface);
}

/**
 * @brief   pushes a message directly to the broker
 * 
 * @param message   a GENERIC_MESSAGE pointer to the message to be sent
 */
void MessageHandler::publishRawMessageToBroker(msg::GENERIC_MESSAGE* message)
{
    if (message == nullptr) 
        return;

    msg::MessageUnion temp;

    msg::conv::convertRawToReal(&temp, message);

    publishers[message->id]->publish((msg::GENERIC_MESSAGE*)(&temp));
}

/**
 * @brief   Pushes a GENERIC_MESSAGE to the IOInterfaces
 * 
 * @param message   a GENERIC_MESSAGE pointer to the message to be sent
 */
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
 * @brief   Initializes IOInterfaces
 * 
 */
void MessageHandler::_initIOInterface()
{
    using namespace IO;
    attachIOInterface(new TCP_Interface());
}

/**
 * @brief   Initializes the IO publishers required by the MessageHandler
 * 
 */
void MessageHandler::_initPublishers()
{
    __ADD_PUBLISHER_TO_MESSAGE_HANDLER(TEST_MESSAGE);
}

/**
 * @brief   Initializes the IO Subscribers required by the MessageHandler
 * 
 */
void MessageHandler::_initSubscribers()
{
    __ADD_SUBSCRIBER_TO_MESSAGE_HANDLER(TEST_MESSAGE_2);
}

void MessageHandler::_messageHandlerThread()
{
    uint8_t* buffer = new uint8_t[2048];

    while(messageHandlerThreadActive)
    {
        for(std::vector<IO::IOInterface*> IOInterfaceVector : IOInterfaceList)
        {
            for(IO::IOInterface* IOInterface : IOInterfaceVector)
            {
                while(IOInterface->isMessageAvailable())
                {
                    int size = IOInterface->readMessage(buffer, IOInterface->getMessageSize());
                    publishRawMessageToBroker((msg::GENERIC_MESSAGE*)buffer);
                }
            }
        }

        usleep(1000);

    }
    delete buffer;
}