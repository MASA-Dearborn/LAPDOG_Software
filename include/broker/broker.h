#pragma once

#include <array>
#include <list>
#include <memory>

#include "publisher.h"
#include "subscriber.h"

namespace pubsub {

    class Broker
    {
    public:
        Broker() {}
        ~Broker();

        msg::GENERIC_MESSAGE* getCurrentMessagePtr(msg::id::MessageType type) { return (msg::GENERIC_MESSAGE*)msg::getMessageAddressFromCollection(MessageCollection, type); }
        int getNumSubscribers(msg::id::MessageType type) { return subscribers[type].size(); }
        int getNumPublishers(msg::id::MessageType type) { return publishers[type].size(); }

    protected:

        /* Registration Methods */
        void registerSubscriber(GenericSubscriber* subscriber);
        void registerPublisher(GenericPublisher* publisher);
        void unregisterSubscriber(GenericSubscriber* subscriber);
        void unregisterPublisher(GenericPublisher* publisher);

        /* Data Methods */        
        void* getLocalDataPointer(msg::id::MessageType type);
        void setMessageUpdateFlag(msg::id::MessageType type);

        void clearSubscribers(msg::id::MessageType type);
        void clearPublishers(msg::id::MessageType type);


        std::array<std::list<std::unique_ptr<GenericSubscriber>>, msg::id::META_NUM_MESSAGES> subscribers;      // Array of Vectors of unique_ptrs to GenericSubscribers
        std::array<std::list<std::unique_ptr<GenericPublisher>>, msg::id::META_NUM_MESSAGES> publishers;        // Array of unique_ptrs to GenericPublishers
        msg::MessageCollection MessageCollection;

        friend class GenericSubscriber;
        friend class GenericPublisher;

    };

    extern Broker DataBroker;

}