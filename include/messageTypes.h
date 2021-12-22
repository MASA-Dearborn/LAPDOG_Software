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

}