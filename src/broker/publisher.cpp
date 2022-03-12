#include "broker/broker.h"
#include "broker/publisher.h"

#include <stdio.h>
#include <string.h>

using namespace pubsub;

void GenericPublisher::_registerSelf()
{
    DataBroker.registerPublisher(this);
}

void GenericPublisher::_pushDataToBroker(void* data, int size)
{
    void* dataLocation = DataBroker.getLocalDataPointer(m_type);
    memcpy(dataLocation, data, size);
    DataBroker.setMessageUpdateFlag(m_type);
}

void GenericPublisher::_unregisterSelf() 
{ 
    DataBroker.unregisterPublisher(this); 
}