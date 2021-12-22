#pragma once
#include "messageTypes.h"

namespace pubsub
{

template <typename T, msg::MessageType msg>
class Subscriber
{
    public:
        Subscriber() {}
        ~Subscriber();

        /* Data Interaction Methods */
        const T* getData();
        bool isDataAvailable();

    protected:

        void setDataAvailable()     { isDataAvailable = true; };
        void clearDataAvailable()   { isDataAvailable = false; };
        void setDataPointer(const T* pointer) { dataPointer = pointer; };

        T* dataPointer = nullptr;
        bool isUpdated = false;
        friend class Broker;

};

}

// USE MACROS TO SIMPLY USER INTERFACE

/**
 *  Subscriber creation registers its self with the broker
 *  Broker stores subscriber in vector of its type
**/