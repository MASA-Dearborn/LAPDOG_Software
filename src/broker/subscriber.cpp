#include "broker/broker.h"
#include "broker/subscriber.h"

using namespace pubsub;

void GenericSubscriber::registerSelf()
{
    DataBroker.registerSubscriber(this);
}
