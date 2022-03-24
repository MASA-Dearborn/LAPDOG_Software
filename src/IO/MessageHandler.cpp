#include "IO/MessageHandler.h"
#include "IO/TCP.h"

#include <unistd.h>

/**
 * @brief   Sets up the the subscribers and publishers of a handler
 * @note    DEFINE NEW MESSAGES HERE
 * 
 * @param   handler     The handler to setup
 */
void defaultMessageHandlerSetup(MessageHandler& handler)
{
    using namespace pubsub;

    /* Attach Publishers */
    handler.attachReceptionPublisher(generatePublisher(msg::id::TEST_MESSAGE_READ));
    handler.attachReceptionPublisher(generatePublisher(msg::id::ALTIMETER_COEFFS));
    handler.attachReceptionPublisher(generatePublisher(msg::id::BNO055_PAGE));
    handler.attachReceptionPublisher(generatePublisher(msg::id::ALTIMETER_COEFFS));
    handler.attachReceptionPublisher(generatePublisher(msg::id::ALTIMETER_DATA));
    handler.attachReceptionPublisher(generatePublisher(msg::id::HUMIDITY_DATA));
    handler.attachReceptionPublisher(generatePublisher(msg::id::BNO055_CAL_ACCEL));
    handler.attachReceptionPublisher(generatePublisher(msg::id::BNO055_CAL_MAG));
    handler.attachReceptionPublisher(generatePublisher(msg::id::BNO055_CAL_GYRO));
    handler.attachReceptionPublisher(generatePublisher(msg::id::BNO055_DATA_ACCEL));
    handler.attachReceptionPublisher(generatePublisher(msg::id::BNO055_DATA_GYRO));
    handler.attachReceptionPublisher(generatePublisher(msg::id::BNO055_DATA_MAG));

    /* Attach Subscribers */
    handler.attachTransmitSubscriber(generateSubscriber(msg::id::TEST_MESSAGE_WRITE));
    handler.attachTransmitSubscriber(generateSubscriber(msg::id::BNO055_ACCEL_CONFIG));
    handler.attachTransmitSubscriber(generateSubscriber(msg::id::BNO055_GYRO_CONFIG));
    handler.attachTransmitSubscriber(generateSubscriber(msg::id::BNO055_MAG_CONFIG));
    handler.attachTransmitSubscriber(generateSubscriber(msg::id::BNO055_OPR_MODE));
    handler.attachTransmitSubscriber(generateSubscriber(msg::id::BNO055_AXIS_CONFIG));
    handler.attachTransmitSubscriber(generateSubscriber(msg::id::BNO055_UNIT_SELECTION));

}

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
            if (IOInterface->isInterfaceValid())
                delete IOInterface;
        }
    }

    for (pubsub::GenericSubscriber* sub : subscribers)
    {
        if (sub != nullptr)
            sub->unsubscribe();
    }

    for (pubsub::GenericPublisher* pub : publishers)
    {
        if (pub != nullptr)
            pub->unregister();
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
    if (interface != nullptr)
        IOInterfaceList[interface->getType()].push_back(interface);
}

/**
 * @brief   Attaches a publisher to publish any recieved messages from interfaces
 * 
 * @param publisher Pointer to a GenericPublisher to add to the MessageHandler
 */
void MessageHandler::attachReceptionPublisher(pubsub::GenericPublisher* publisher)
{
    if (publisher != nullptr)
        publishers[publisher->getType()] = publisher;
}

/**
 * @brief   Attaches a subscriber to recieve messages to transmit to interfaces
 * 
 * @param subscriber Pointer to a GenericSubscriber to add to the MessageHandler
 */
void MessageHandler::attachTransmitSubscriber(pubsub::GenericSubscriber* subscriber)
{
    if (subscriber != nullptr)
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
        if (interface->isInterfaceValid())
            interface->writeMessage((uint8_t*)message, message->size);
    }
}

/**
 * @brief   Pushes a GENERIC_MESSAGE to the IOInterfaces
 * @note    DEFINE NEW MESSAGES HERE
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
        __sendMessageToInterfaces(this->IOInterfaceList[IO::TYPE_I2C], &converted_message.TEST_MESSAGE_WRITE);
        __sendMessageToInterfaces(this->IOInterfaceList[IO::TYPE_SPI], &converted_message.TEST_MESSAGE_WRITE);
        __sendMessageToInterfaces(this->IOInterfaceList[IO::TYPE_CAN], &converted_message.TEST_MESSAGE_WRITE);
        __sendMessageToInterfaces(this->IOInterfaceList[IO::TYPE_GENERIC], &converted_message.TEST_MESSAGE_WRITE);
        break;
    case msg::id::BNO055_PAGE:
        break;
    case msg::id::ALTIMETER_COEFFS:
        break;
    case msg::id::ALTIMETER_DATA:
        break;
    case msg::id::HUMIDITY_DATA:
        break;
    case msg::id::BNO055_ACCEL_CONFIG:
        __sendMessageToInterfaces(this->IOInterfaceList[IO::TYPE_I2C], &converted_message.BNO055_ACCEL_CONFIG);
        break;
    case msg::id::BNO055_GYRO_CONFIG:
        __sendMessageToInterfaces(this->IOInterfaceList[IO::TYPE_I2C], &converted_message.BNO055_GYRO_CONFIG);
        break;
    case msg::id::BNO055_MAG_CONFIG:
        __sendMessageToInterfaces(this->IOInterfaceList[IO::TYPE_I2C], &converted_message.BNO055_MAG_CONFIG);
        break;
    case msg::id::BNO055_OPR_MODE:
        __sendMessageToInterfaces(this->IOInterfaceList[IO::TYPE_I2C], &converted_message.BNO055_OPR_MODE);
        break;
    case msg::id::BNO055_AXIS_CONFIG:
        __sendMessageToInterfaces(this->IOInterfaceList[IO::TYPE_I2C], &converted_message.BNO055_AXIS_CONFIG);
        break;
    case msg::id::BNO055_UNIT_SELECTION:
        __sendMessageToInterfaces(this->IOInterfaceList[IO::TYPE_I2C], &converted_message.BNO055_UNIT_SELECTION);
        break;
    case msg::id::BNO055_CAL_ACCEL:
        break;
    case msg::id::BNO055_CAL_MAG:
        break;
    case msg::id::BNO055_CAL_GYRO:
        break;
    case msg::id::BNO055_DATA_ACCEL:
        break;
    case msg::id::BNO055_DATA_GYRO:
        break;
    case msg::id::BNO055_DATA_MAG:
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
                while(IOInterface->isInterfaceValid() && IOInterface->isMessageAvailable())
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
                sendSubscribedToIO(sub->getGenericPointer());
            }
        }

        usleep(1000);

    }
    delete buffer;
}