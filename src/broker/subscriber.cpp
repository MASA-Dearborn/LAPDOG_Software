#include "broker/broker.h"
#include "broker/subscriber.h"

using namespace pubsub;

void GenericSubscriber::registerSelf()
{
    DataBroker.registerSubscriber(this);
}

void GenericSubscriber::unregisterSelf()
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