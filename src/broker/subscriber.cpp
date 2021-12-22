#include "broker/broker.h"
#include "broker/subscriber.h"

using namespace pubsub;

template <typename T>
Subscriber<T>::Subscriber(msg::ids::MessageType type) 
{ 
    m_type = type; 
}