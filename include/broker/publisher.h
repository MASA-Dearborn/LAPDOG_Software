#pragma once
#include "messageTypes.h"

namespace pubsub
{

    class GenericPublisher
    {
        public:
            GenericPublisher() {}
            ~GenericPublisher() {}
            msg::ids::MessageType getType() const { return m_type; }

        protected:
            msg::ids::MessageType m_type;

    };

    template <typename T>
    class Publisher : public GenericPublisher
    {
        public:
            Publisher() {}
            Publisher(msg::ids::MessageType type);
            ~Publisher() {}
            void publishData(T& data);

    };

    template <typename T>
    Publisher<T> publish(msg::ids::MessageType type)
    {
        return Publisher<T>(type);
    }

    #define createPublisher(Message)    publish<msg::types::Message>(msg::ids::Message)

}