#include "broker/broker.h"
#include "broker/publisher.h"

using namespace pubsub;

template <typename T>
Publisher<T>::Publisher(msg::ids::MessageType type)
{
    m_type = type;
}