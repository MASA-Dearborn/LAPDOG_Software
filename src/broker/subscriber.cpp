#include "broker/broker.h"
#include "broker/subscriber.h"

using namespace pubsub;

void GenericSubscriber::_registerSelf()
{
    DataBroker.registerSubscriber(this);
}

void GenericSubscriber::_unregisterSelf()
{
    DataBroker.unregisterSubscriber(this);
}

bool GenericSubscriber::isDataAvailable()
{ 
    m_lock.lock();
    bool temp = m_isDataAvailable;
    m_lock.unlock();
    return temp; 
}

void GenericSubscriber::setDataAvailable()     
{ 
    m_lock.lock();
    m_isDataAvailable = true; 
    m_lock.unlock();
}

void GenericSubscriber::clearDataAvailable()   
{ 
    m_lock.lock();
    m_isDataAvailable = false; 
    m_lock.unlock();
}

void GenericSubscriber::unsubscribe() 
{ 
    this->~GenericSubscriber(); 
}

GenericSubscriber* pubsub::generateSubscriber(msg::id::MessageType type)
{
    GenericSubscriber* subscriber = new GenericSubscriber();
    subscriber->m_type = type;
    subscriber->m_isDataAvailable;
    subscriber->_registerSelf();
    return subscriber;
}