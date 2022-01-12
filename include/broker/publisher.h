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
            void registerSelf();
            void unregisterSelf();

            void _pushDataToBroker(void* data, int size);

            msg::id::MessageType m_type;
            unsigned int m_size;

    };

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
                registerSelf();
            }

    };

    template <typename T>
    Publisher<T>* constructPublisher(msg::id::MessageType type)
    {
        return new Publisher<T>(type);
    }

    #define createNewPublisher(Message)    pubsub::constructPublisher<msg::real::Message>(msg::id::Message)

}