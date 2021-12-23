#include "broker/broker.h"

using namespace pubsub;

Broker pubsub::DataBroker;

void Broker::registerSubscriber(GenericSubscriber* subscriber)
{
    subscribers[subscriber->getType()].push_back(std::unique_ptr<GenericSubscriber>(subscriber));
}

void Broker::registerPublisher(GenericPublisher* publisher)
{
    publishers[publisher->getType()] = std::unique_ptr<GenericPublisher>(publisher);
}

void Broker::unregisterSubscriber(GenericSubscriber* subscriber)
{
    for(int i = 0; i < subscribers[subscriber->getType()].size(); i++)
    {
        if(subscribers[subscriber->getType()][i].get() == subscriber)
        {
            subscribers[subscriber->getType()].erase(subscribers[subscriber->getType()].begin() + i);
            return;
        }
    }
}

void Broker::unregisterPublisher(GenericPublisher* publisher)
{
    // TODO: Implement
}
