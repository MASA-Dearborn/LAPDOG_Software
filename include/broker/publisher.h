#pragma once
#include "../messageTypes.h"

namespace pubsub
{

    class GenericPublisher
    {
        public:
            GenericPublisher() {}
            ~GenericPublisher() {}

            void unregister() { this->~GenericPublisher(); }
            msg::id::MessageType getType() const { return m_type; }

            void publish(void* data)
            {
                _pushDataToBroker(data, m_size);
            }

        protected:

            friend class Broker;
            friend GenericPublisher* generatePublisher(msg::id::MessageType type);
            void _registerSelf();
            void _unregisterSelf();
            void _pushDataToBroker(void* data, int size);

            msg::id::MessageType m_type = msg::id::UNDEFINED_MESSAGE;
            unsigned int m_size;
    };

    GenericPublisher* generatePublisher(msg::id::MessageType type);

    template <typename T>
    class Publisher : public GenericPublisher
    {
        public:
            Publisher() {}
            ~Publisher() {}
            Publisher(msg::id::MessageType type)
            {
                m_type = type;
                m_size = sizeof(T);
                _registerSelf();
            }

    };

    template <typename T>
    Publisher<T>* constructPublisher(msg::id::MessageType type)
    {
        return new Publisher<T>(type);
    }

    #define createNewPublisher(Message)    pubsub::constructPublisher<msg::real::Message>(msg::id::Message)

}