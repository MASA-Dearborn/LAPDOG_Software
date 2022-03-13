#include "IO/MessageHandler.h"
#include "IO/TCP.h"

#include <unistd.h>

#define __ADD_PUBLISHER_TO_MESSAGE_HANDLER(name)     publishers[msg::id::name] = createNewPublisher(name)
#define __ADD_SUBSCRIBER_TO_MESSAGE_HANDLER(name)    subscribers[msg::id::name] = createNewSubscriber(name)

MessageHandler::MessageHandler()
{
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
            if (IOInterface->getType() != IO::TYPE_UNDEFINED)
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
    if (interface != NULL)
        IOInterfaceList[interface->getType()].push_back(interface);
}

/**
 * @brief   Attaches a publisher to publish any recieved messages from interfaces
 * 
 * @param publisher Pointer to a GenericPublisher to add to the MessageHandler
 */
void MessageHandler::attachReceptionPublisher(pubsub::GenericPublisher* publisher)
{
    if (publisher != NULL)
        publishers[publisher->getType()] = publisher;
}

/**
 * @brief   Attaches a subscriber to recieve messages to transmit to interfaces
 * 
 * @param subscriber Pointer to a GenericSubscriber to add to the MessageHandler
 */
void MessageHandler::attachTransmitSubscriber(pubsub::GenericSubscriber* subscriber)
{
    if (subscriber != NULL)
        subscribers[subscriber->getType()] = subscriber;
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

    msg::RealMessageUnion temp;

    msg::conv::convertRawToReal(&temp, message);

    if (publishers[message->id] != nullptr)
        publishers[message->id]->publish((msg::GENERIC_MESSAGE*)(&temp));
}

/**
 * @brief   Transmits a message to all the interfaces contained in a vector
 * 
 * @param interfaceVector   The vector containting pointers to interfaces to transmit to
 * @param message           The message to transmit
 */
static void __sendMessageToInterfaces(std::vector<IO::IOInterface*>& interfaceVector, msg::GENERIC_MESSAGE* message)
{
    for (IO::IOInterface* interface : interfaceVector)
    {
        interface->writeMessage((uint8_t*)message, message->size);
    }
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

    msg::RawMessageUnion converted_message;
    msg::conv::convertRealToRaw(&converted_message, message);

    // Send message to different Interface depending on the type
    switch ( message->id )
    {
    case msg::id::TEST_MESSAGE_READ:
        __sendMessageToInterfaces(this->IOInterfaceList[IO::TYPE_TCP], &converted_message.TEST_MESSAGE_READ);
        __sendMessageToInterfaces(this->IOInterfaceList[IO::TYPE_GENERIC], &converted_message.TEST_MESSAGE_READ);
        break;
    case msg::id::TEST_MESSAGE_WRITE:
        __sendMessageToInterfaces(this->IOInterfaceList[IO::TYPE_TCP], &converted_message.TEST_MESSAGE_WRITE);
        __sendMessageToInterfaces(this->IOInterfaceList[IO::TYPE_GENERIC], &converted_message.TEST_MESSAGE_WRITE);
        break;
    default:
        printf("MessageHandler: sendSubscribedToIO - message not defined\n");
        break;
    }

}

/**
 * @brief   Initializes IOInterfaces
 * 
 */
void MessageHandler::_initIOInterface()
{
    using namespace IO;
}

/**
 * @brief   The main thread for a MessageHandler
 * 
 */
void MessageHandler::_messageHandlerThread()
{
    uint8_t* buffer = new uint8_t[2048];

    while(messageHandlerThreadActive)
    {

        // Check each IOInterface for an incomming message
        for(std::vector<IO::IOInterface*> IOInterfaceVector : IOInterfaceList)
        {
            for(IO::IOInterface* IOInterface : IOInterfaceVector)
            {
                while(IOInterface->isMessageAvailable() && IOInterface->getType() != IO::TYPE_UNDEFINED)
                {
                    int size = IOInterface->readMessage(buffer, IOInterface->getMessageSize());
                    publishRawMessageToBroker((msg::GENERIC_MESSAGE*)buffer);
                }
            }
        }
        
        // Check each subscriber for recieved data to send
        for(pubsub::GenericSubscriber* sub: subscribers)
        {
            if(sub == nullptr)
                continue;
            
            if(sub->isDataAvailable())
            {
                // TODO: How to get data from generic subscriber without breaking architecture
                // Maybe get the data pointer using a generic message cast and send that?
                sendSubscribedToIO(sub->getGenericPointer());
            }
            
        }

        usleep(1000);

    }
    delete buffer;
}