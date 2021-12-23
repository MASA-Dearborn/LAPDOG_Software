#include "broker/broker.h"

#include <algorithm>

using namespace pubsub;

Broker pubsub::DataBroker;

Broker::~Broker()
{
    for(int i = 0; i < (int)msg::ids::META_NUM_MESSAGES; i++)
    {
        clearSubscribers((msg::ids::MessageType)i);
    }
}

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

    msg::ids::MessageType type = subscriber->getType();

    for(std::list<std::unique_ptr<GenericSubscriber>>::iterator iter = subscribers[type].begin(); iter != subscribers[type].end();)
    {
        if(iter->get() == subscriber)
        {
            iter = subscribers[type].erase(iter);
        } else {
            ++iter;
        }
    }

}

void Broker::unregisterPublisher(GenericPublisher* publisher)
{
    // TODO: Implement
}