#include "broker/broker.h"
#include <algorithm>

using namespace pubsub;

Broker pubsub::DataBroker;

/**
 * @brief Destroy the Broker:: Broker object and clear all existing subscribers
 * 
 */
Broker::~Broker()
{
    for(int i = 0; i < (int)msg::ids::META_NUM_MESSAGES; i++)
    {
        clearSubscribers((msg::ids::MessageType)i);
    }
}

/**
 * @brief   Registers a subscriber to the broker
 * 
 * @param   subscriber  Subscriber to register
 */
void Broker::registerSubscriber(GenericSubscriber* subscriber)
{
    subscriber->setDataPointer(getLocalDataPointer(subscriber->getType()));
    subscribers[subscriber->getType()].push_back(std::unique_ptr<GenericSubscriber>(subscriber));
}

/**
 * @brief   Registers a publisher to the broker
 * 
 * @param   publisher   Publisher to register
 */
void Broker::registerPublisher(GenericPublisher* publisher)
{
    publishers[publisher->getType()] = std::unique_ptr<GenericPublisher>(publisher);
}

/**
 * @brief   Unregister a subscriber from the broker
 * 
 * @param   subscriber  Subscriber to remove
 */
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

/**
 * @brief   Unregister a publisher from the broker
 * 
 * @param   publisher   Publisher to remove
 */
void Broker::unregisterPublisher(GenericPublisher* publisher)
{
    // TODO: Implement
}

/**
 * @brief   Get the Local Data Pointer for the MessageType
 * @note    Add new messages here
 * 
 * @param   type    The Enum ID of the message pointer to recieve 
 * @return  void*   Void pointer to data location 
 */
void* Broker::getLocalDataPointer(msg::ids::MessageType type)
{
    return msg::getMessageAddressFromCollection(MessageCollection, type);
}


void Broker::setMessageUpdateFlag(msg::ids::MessageType type)
{

    auto setFlag = [](std::unique_ptr<GenericSubscriber>& sub)
    {
        sub->setDataAvailable();
    };

    std::for_each(subscribers[type].begin(), subscribers[type].end(), setFlag);

}