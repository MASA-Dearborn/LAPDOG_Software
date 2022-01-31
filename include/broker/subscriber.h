#pragma once
#include "../messageTypes.h"
#include <mutex>

namespace pubsub
{

    class GenericSubscriber
    {
        public:
            GenericSubscriber() {}
            ~GenericSubscriber() { unregisterSelf(); }

            bool isDataAvailable();
            void setDataAvailable();
            void clearDataAvailable();
            void unsubscribe();

            void setDataPointer(void* source) { m_dataPointer = source; }
            msg::GENERIC_MESSAGE* getGenericPointer() { return (msg::GENERIC_MESSAGE*)m_dataPointer; }
            msg::id::MessageType getType() const { return m_type; };

        protected:

            friend class Broker;
            void registerSelf();
            void unregisterSelf();

            std::mutex m_lock;
            msg::id::MessageType m_type = msg::id::UNDEFINED_MESSAGE;
            bool m_isDataAvailable;
            void* m_dataPointer = nullptr;
    };

    /**
     * @brief   A type specific implementation of a subscriber. Should be used for messaging system subscriptions
     * 
     * @tparam  T   A type to subscribe to
     */
    template <typename T>
    class Subscriber : public GenericSubscriber
    {
        public:
            Subscriber() {}

            Subscriber(msg::id::MessageType type)
            {
                m_type = type; 
                m_isDataAvailable = false;
                registerSelf();
            }

            ~Subscriber() { unregisterSelf(); }
            const T* getData() 
            {
                clearDataAvailable(); 
                return (T*)m_dataPointer; 
            }
    };


    /**
     * @brief   Interface function to generate a subscriber based on type enum
     * 
     * @param   type    The MessageType enum of the message to subscribe to
     * @return  GenericSubscriber derived from Subscriber<T> configured for message of type 
     */
    template <typename T>
    Subscriber<T>* constructSubscriber(msg::id::MessageType type)
    {
        return new Subscriber<T>(type);
    }

    #define createNewSubscriber(Message)    pubsub::constructSubscriber<msg::real::Message>(msg::id::Message)

}
