#include "broker/subscriber.h"
#include "broker/broker.h"

using namespace pubsub;

template <typename T>
Subscriber<T>::Subscriber()
{
    DataBroker.test();
}

template <typename T>
Subscriber<T>::~Subscriber()
{

}