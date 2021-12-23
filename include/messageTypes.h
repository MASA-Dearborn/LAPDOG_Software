#pragma once

namespace msg
{

    /* Enum Namespace */
    namespace ids
    {
        enum MessageType
        {
            TEST_MESSAGE = 0,
            META_NUM_MESSAGES,
            UNDEFINED_MESSAGE,
        };
    }

    /* Message Declarations */
    namespace types
    {

        struct TEST_MESSAGE
        {
            int test;
        };

    }

    /* Overall Message Structure */
    struct MessageCollection
    {
        types::TEST_MESSAGE TEST_MESSAGE;
    };

    /**
    * @brief   Get the Relative Data Pointer for the MessageType in collection
    * @note    Add new messages here
    * 
    * @param   collection   MessageCollection reference
    * @param   type         The Enum ID of the message pointer to recieve 
    * @return  void*        Void pointer to data location 
    */
    inline void* getMessageAddressFromCollection(MessageCollection& collection, const ids::MessageType type)
    {
        using namespace ids;
        switch(type)
        {
            case TEST_MESSAGE:
                return &collection.TEST_MESSAGE;
            default:
                return nullptr;
        }
    }

}