#pragma once

#include <array>

#include "../messageTypes.h"
#include "../broker/broker.h"
#include "IOInterface.h"

class MessageHandler
{
    public:
        MessageHandler();
        ~MessageHandler();

    protected:

        void publishMessageToBroker(msg::GENERIC_MESSAGE* message);
        void sendSubscribedToIO(msg::GENERIC_MESSAGE* message);

        void _initPublishers();
        void _initSubscribers();

    private:

        friend class IOInterface;
        std::array<pubsub::GenericPublisher*, msg::id::META_NUM_MESSAGES> publishers;
        std::array<pubsub::GenericPublisher*, msg::id::META_NUM_MESSAGES> subscribers;
        

};