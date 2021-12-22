#pragma once
#include "publisher.h"
#include "subscriber.h"

namespace pubsub {

    class Broker
    {
    public:

        
    protected:
        // Array of vectors for each subscriber type
        msg::MessageCollection MessageCollection;

    };

    extern Broker DataBroker;

}