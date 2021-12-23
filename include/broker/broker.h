#pragma once

#include <array>
#include <vector>
#include <memory>

#include "publisher.h"
#include "subscriber.h"

namespace pubsub {

    class Broker
    {
    public:
        Broker() {}
        ~Broker() {}

        int getNumSubscribers(msg::ids::MessageType type) { return subscribers[type].size(); }
        
        void registerSubscriber(GenericSubscriber* subscriber);
        void registerPublisher(GenericPublisher* publisher);
        void unregisterSubscriber(GenericSubscriber* subscriber);
        void unregisterPublisher(GenericPublisher* publisher);

        void clearSubscribers(msg::ids::MessageType type) { subscribers[type].erase(subscribers[type].begin(), subscribers[type].end()); }

    protected:

        std::array<std::vector<std::unique_ptr<GenericSubscriber>>, msg::ids::META_NUM_MESSAGES> subscribers;   // Array of Vectors of unique_ptrs to GenericSubscribers
        std::array<std::unique_ptr<GenericPublisher>, msg::ids::META_NUM_MESSAGES> publishers;                  // Array of unique_ptrs to GenericPublishers
        msg::MessageCollection MessageCollection;

        friend class GenericSubscriber;
        friend class GenericPublisher;

    };

    extern Broker DataBroker;

}