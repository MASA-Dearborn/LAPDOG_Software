#pragma once

#include <array>
#include <thread>
#include <vector>

#include "../messageTypes.h"
#include "../broker/broker.h"
#include "IOInterface.h"


class MessageHandler
{
    public:
        MessageHandler();
        ~MessageHandler();

        void attachIOInterface(IO::IOInterface* interface);
        void attachReceptionPublisher(pubsub::GenericPublisher* publisher);
        void attachTransmitSubscriber(pubsub::GenericSubscriber* subscriber);

    protected:

        void publishRawMessageToBroker(msg::GENERIC_MESSAGE* message);
        void sendSubscribedToIO(msg::GENERIC_MESSAGE* message);

        void _initPublishers();
        void _initSubscribers();
        void _initIOInterface();
        void _messageHandlerThread();

        friend class IOInterface;
        std::array<std::vector<IO::IOInterface*>, IO::NUM_TYPES> IOInterfaceList;

        std::array<pubsub::GenericPublisher*, msg::id::META_NUM_MESSAGES> publishers {nullptr};
        std::array<pubsub::GenericSubscriber*, msg::id::META_NUM_MESSAGES> subscribers {nullptr};
        
        std::thread messageHandlerThreadObj;
        bool messageHandlerThreadActive = true;
};