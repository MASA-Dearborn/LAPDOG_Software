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
