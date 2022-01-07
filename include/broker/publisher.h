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

        protected:

            friend class Broker;
            void registerSelf();
            void unregisterSelf();

            void _pushDataToBroker(void* data, int size);

            msg::id::MessageType m_type;

    };

    template <typename T>
    class Publisher : public GenericPublisher
    {
        public:
            Publisher() {}
            Publisher(msg::id::MessageType type)
            {
                m_type = type;
                registerSelf();
            }
            ~Publisher() {}
            
            void unregister() { this->~GenericPublisher(); }
            void publish(T* data)
            {
                _pushDataToBroker(data, sizeof(T));
            }

    };

    template <typename T>
    Publisher<T>* constructPublisher(msg::id::MessageType type)
    {
        return new Publisher<T>(type);
    }

    #define createNewPublisher(Message)    pubsub::constructPublisher<msg::real::Message>(msg::id::Message)

}