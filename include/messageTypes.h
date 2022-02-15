/* Auto-generated Code from messageGenerator.py */

#pragma once
#include <string.h>
#include <stdio.h>

#define MAX_RAW_MESSAGE_SIZE sizeof(msg::RawMessageUnion)
#define MAX_REAL_MESSAGE_SIZE sizeof(msg::RealMessageUnion)

namespace msg::id {

    enum MessageType {
        TEST_MESSAGE = 0,
        TEST_MESSAGE_2 = 1,
        META_NUM_MESSAGES,
        UNDEFINED_MESSAGE,
    };
    
}

namespace msg {

    struct GENERIC_MESSAGE {
        msg::id::MessageType id = msg::id::UNDEFINED_MESSAGE;
        unsigned int size = sizeof(GENERIC_MESSAGE);
    };

}

namespace msg::real {

    struct TEST_MESSAGE : GENERIC_MESSAGE {
        TEST_MESSAGE() { id = msg::id::TEST_MESSAGE; size = sizeof(TEST_MESSAGE); }
        int test;
        float VAR2 = 5.2;
    };
    
    struct TEST_MESSAGE_2 : GENERIC_MESSAGE {
        TEST_MESSAGE_2() { id = msg::id::TEST_MESSAGE_2; size = sizeof(TEST_MESSAGE_2); }
        int VAR1;
        float VAR2 = 0.23;
    };
    
}

namespace msg::raw {

    struct TEST_MESSAGE : GENERIC_MESSAGE {
        TEST_MESSAGE() { id = msg::id::TEST_MESSAGE; size = sizeof(TEST_MESSAGE); }
        int test : 10;
        int VAR2 : 16;
    };
    
    struct TEST_MESSAGE_2 : GENERIC_MESSAGE {
        TEST_MESSAGE_2() { id = msg::id::TEST_MESSAGE_2; size = sizeof(TEST_MESSAGE_2); }
        int VAR1 : 10;
        int VAR2 : 16;
    };
    
}

namespace msg {

    struct MessageCollection {
        real::TEST_MESSAGE TEST_MESSAGE;
        real::TEST_MESSAGE_2 TEST_MESSAGE_2;
    };
    
    union RealMessageUnion {
        RealMessageUnion() { memset( this, 0, sizeof( RealMessageUnion ) ); }
        real::TEST_MESSAGE TEST_MESSAGE;
        real::TEST_MESSAGE_2 TEST_MESSAGE_2;
    };
    
    union RawMessageUnion {
        RawMessageUnion() { memset( this, 0, sizeof( RawMessageUnion ) ); }
        raw::TEST_MESSAGE TEST_MESSAGE;
        raw::TEST_MESSAGE_2 TEST_MESSAGE_2;
    };
    
    inline void* getMessageAddressFromCollection(MessageCollection& collection, const id::MessageType type) {
        switch (type) {
            case msg::id::TEST_MESSAGE:
                return &collection.TEST_MESSAGE;
            case msg::id::TEST_MESSAGE_2:
                return &collection.TEST_MESSAGE_2;
            default:
                return nullptr;
        }
    }
    
}

namespace msg::conv {

    inline msg::real::TEST_MESSAGE TEST_MESSAGE_TO_REAL(msg::raw::TEST_MESSAGE* raw) {
        msg::real::TEST_MESSAGE real;
        real.test = (raw->test * 1) + 0;
        real.VAR2 = (raw->VAR2 * 0.00152587890625) + 0;
        return real;
    }
    
    inline msg::real::TEST_MESSAGE_2 TEST_MESSAGE_2_TO_REAL(msg::raw::TEST_MESSAGE_2* raw) {
        msg::real::TEST_MESSAGE_2 real;
        real.VAR1 = (raw->VAR1 * 1) + 0;
        real.VAR2 = (raw->VAR2 * 0.0030517578125) + 0;
        return real;
    }
    
    inline msg::raw::TEST_MESSAGE TEST_MESSAGE_TO_RAW(msg::real::TEST_MESSAGE* real) {
        msg::raw::TEST_MESSAGE raw;
        raw.test = (real->test - 0) / 1;
        raw.VAR2 = (real->VAR2 - 0) / 0.00152587890625;
        return raw;
    }
    
    inline msg::raw::TEST_MESSAGE_2 TEST_MESSAGE_2_TO_RAW(msg::real::TEST_MESSAGE_2* real) {
        msg::raw::TEST_MESSAGE_2 raw;
        raw.VAR1 = (real->VAR1 - 0) / 1;
        raw.VAR2 = (real->VAR2 - 0) / 0.0030517578125;
        return raw;
    }
    
    inline msg::id::MessageType convertRawToReal(msg::RealMessageUnion* dest, GENERIC_MESSAGE* raw) {
        switch(raw->id) {
            case msg::id::TEST_MESSAGE:
                dest->TEST_MESSAGE = msg::conv::TEST_MESSAGE_TO_REAL((msg::raw::TEST_MESSAGE*)(raw));
                break;
            case msg::id::TEST_MESSAGE_2:
                dest->TEST_MESSAGE_2 = msg::conv::TEST_MESSAGE_2_TO_REAL((msg::raw::TEST_MESSAGE_2*)(raw));
                break;
        }
        return raw->id;
    }
    
    inline msg::id::MessageType convertRealToRaw(msg::RawMessageUnion* dest, GENERIC_MESSAGE* real) {
        switch(real->id) {
            case msg::id::TEST_MESSAGE:
                dest->TEST_MESSAGE = msg::conv::TEST_MESSAGE_TO_RAW((msg::real::TEST_MESSAGE*)(real));
                break;
            case msg::id::TEST_MESSAGE_2:
                dest->TEST_MESSAGE_2 = msg::conv::TEST_MESSAGE_2_TO_RAW((msg::real::TEST_MESSAGE_2*)(real));
                break;
        }
        return real->id;
    }
    
    inline void stringifyRealMessage(char* dest, msg::GENERIC_MESSAGE* message) {
        switch(message->id) {
        case msg::id::TEST_MESSAGE:
            sprintf(dest, "%d %.3f ", 
                    ((msg::real::TEST_MESSAGE*)message)->test, 
                    ((msg::real::TEST_MESSAGE*)message)->VAR2);
            break;
        case msg::id::TEST_MESSAGE_2:
            sprintf(dest, "%d %.3f ", 
                    ((msg::real::TEST_MESSAGE_2*)message)->VAR1, 
                    ((msg::real::TEST_MESSAGE_2*)message)->VAR2);
            break;
        }
    }
    
}

