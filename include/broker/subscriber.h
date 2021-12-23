#pragma once
#include "messageTypes.h"

namespace pubsub
{

    class GenericSubscriber
    {
        public:
            GenericSubscriber() {}
            ~GenericSubscriber() {}

            bool isDataAvailable()      { return m_isDataAvailable; }
            void setDataAvailable()     { m_isDataAvailable = true; };
            void clearDataAvailable()   { m_isDataAvailable = false; };

            void setDataPointer(void* source) { m_dataPointer = source; }
            msg::ids::MessageType getType() const { return m_type; };

        protected:

            friend class Broker;
            void registerSelf();

            msg::ids::MessageType m_type = msg::ids::UNDEFINED_MESSAGE;
            bool m_isDataAvailable = false;
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

            Subscriber(msg::ids::MessageType type)
            {
                m_type = type; 
                registerSelf();
            }

            ~Subscriber() {}
            const T* getData() { return (T*)m_dataPointer; }
    };


    /**
     * @brief   Interface function to generate a subscriber based on type enum
     * 
     * @param   type    The MessageType enum of the message to subscribe to
     * @return  GenericSubscriber derived from Subscriber<T> configured for message of type 
     */
    template <typename T>
    Subscriber<T> subscribe(msg::ids::MessageType type)
    {
        return Subscriber<T>(type);
    }

    #define createSubscriber(Message)    subscribe<msg::types::Message>(msg::ids::Message)

}
