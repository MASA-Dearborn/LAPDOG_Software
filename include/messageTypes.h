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
        ALTIMETER_COEFFS = 2,
        ALTIMETER_DATA = 3,
        HUMIDITY_DATA = 4,
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
    
    struct ALTIMETER_COEFFS : GENERIC_MESSAGE {
        ALTIMETER_COEFFS() { id = msg::id::ALTIMETER_COEFFS; size = sizeof(ALTIMETER_COEFFS); }
        unsigned int coeff_1;
        unsigned int coeff_2;
        unsigned int coeff_3;
        unsigned int coeff_4;
        unsigned int coeff_5;
        unsigned int coeff_6;
    };
    
    struct ALTIMETER_DATA : GENERIC_MESSAGE {
        ALTIMETER_DATA() { id = msg::id::ALTIMETER_DATA; size = sizeof(ALTIMETER_DATA); }
        float pressure_bar;
        float temp_celcius;
    };
    
    struct HUMIDITY_DATA : GENERIC_MESSAGE {
        HUMIDITY_DATA() { id = msg::id::HUMIDITY_DATA; size = sizeof(HUMIDITY_DATA); }
        float relative_humidity;
        float temp_celcius;
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
    
    struct ALTIMETER_COEFFS : GENERIC_MESSAGE {
        ALTIMETER_COEFFS() { id = msg::id::ALTIMETER_COEFFS; size = sizeof(ALTIMETER_COEFFS); }
        int coeff_1 : 16;
        int coeff_2 : 16;
        int coeff_3 : 16;
        int coeff_4 : 16;
        int coeff_5 : 16;
        int coeff_6 : 16;
    };
    
    struct ALTIMETER_DATA : GENERIC_MESSAGE {
        ALTIMETER_DATA() { id = msg::id::ALTIMETER_DATA; size = sizeof(ALTIMETER_DATA); }
        int pressure_bar : 24;
        int temp_celcius : 24;
    };
    
    struct HUMIDITY_DATA : GENERIC_MESSAGE {
        HUMIDITY_DATA() { id = msg::id::HUMIDITY_DATA; size = sizeof(HUMIDITY_DATA); }
        int relative_humidity : 10;
        int temp_celcius : 12;
    };
    
}

namespace msg {

    const int RAW_MESSAGE_SIZES[] = {
        sizeof(msg::raw::TEST_MESSAGE),
        sizeof(msg::raw::TEST_MESSAGE_2),
        sizeof(msg::raw::ALTIMETER_COEFFS),
        sizeof(msg::raw::ALTIMETER_DATA),
        sizeof(msg::raw::HUMIDITY_DATA),
    };
    
    const int REAL_MESSAGE_SIZES[] = {
        sizeof(msg::real::TEST_MESSAGE),
        sizeof(msg::real::TEST_MESSAGE_2),
        sizeof(msg::real::ALTIMETER_COEFFS),
        sizeof(msg::real::ALTIMETER_DATA),
        sizeof(msg::real::HUMIDITY_DATA),
    };
    
    struct MessageCollection {
        real::TEST_MESSAGE TEST_MESSAGE;
        real::TEST_MESSAGE_2 TEST_MESSAGE_2;
        real::ALTIMETER_COEFFS ALTIMETER_COEFFS;
        real::ALTIMETER_DATA ALTIMETER_DATA;
        real::HUMIDITY_DATA HUMIDITY_DATA;
    };
    
    union RealMessageUnion {
        RealMessageUnion() { memset( this, 0, sizeof( RealMessageUnion ) ); }
        real::TEST_MESSAGE TEST_MESSAGE;
        real::TEST_MESSAGE_2 TEST_MESSAGE_2;
        real::ALTIMETER_COEFFS ALTIMETER_COEFFS;
        real::ALTIMETER_DATA ALTIMETER_DATA;
        real::HUMIDITY_DATA HUMIDITY_DATA;
    };
    
    union RawMessageUnion {
        RawMessageUnion() { memset( this, 0, sizeof( RawMessageUnion ) ); }
        raw::TEST_MESSAGE TEST_MESSAGE;
        raw::TEST_MESSAGE_2 TEST_MESSAGE_2;
        raw::ALTIMETER_COEFFS ALTIMETER_COEFFS;
        raw::ALTIMETER_DATA ALTIMETER_DATA;
        raw::HUMIDITY_DATA HUMIDITY_DATA;
    };
    
    inline void* getMessageAddressFromCollection(MessageCollection& collection, const id::MessageType type) {
        switch (type) {
            case msg::id::TEST_MESSAGE:
                return &collection.TEST_MESSAGE;
            case msg::id::TEST_MESSAGE_2:
                return &collection.TEST_MESSAGE_2;
            case msg::id::ALTIMETER_COEFFS:
                return &collection.ALTIMETER_COEFFS;
            case msg::id::ALTIMETER_DATA:
                return &collection.ALTIMETER_DATA;
            case msg::id::HUMIDITY_DATA:
                return &collection.HUMIDITY_DATA;
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
    
    inline msg::real::ALTIMETER_COEFFS ALTIMETER_COEFFS_TO_REAL(msg::raw::ALTIMETER_COEFFS* raw) {
        msg::real::ALTIMETER_COEFFS real;
        real.coeff_1 = (raw->coeff_1 * 1) + 0;
        real.coeff_2 = (raw->coeff_2 * 1) + 0;
        real.coeff_3 = (raw->coeff_3 * 1) + 0;
        real.coeff_4 = (raw->coeff_4 * 1) + 0;
        real.coeff_5 = (raw->coeff_5 * 1) + 0;
        real.coeff_6 = (raw->coeff_6 * 1) + 0;
        return real;
    }
    
    inline msg::real::ALTIMETER_DATA ALTIMETER_DATA_TO_REAL(msg::raw::ALTIMETER_DATA* raw) {
        msg::real::ALTIMETER_DATA real;
        real.pressure_bar = (raw->pressure_bar * 2.980232238769531e-07) + 0;
        real.temp_celcius = (raw->temp_celcius * 7.450580596923828e-06) + -40;
        return real;
    }
    
    inline msg::real::HUMIDITY_DATA HUMIDITY_DATA_TO_REAL(msg::raw::HUMIDITY_DATA* raw) {
        msg::real::HUMIDITY_DATA real;
        real.relative_humidity = (raw->relative_humidity * 0.09765625) + 0;
        real.temp_celcius = (raw->temp_celcius * 0.040283203125) + -40;
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
    
    inline msg::raw::ALTIMETER_COEFFS ALTIMETER_COEFFS_TO_RAW(msg::real::ALTIMETER_COEFFS* real) {
        msg::raw::ALTIMETER_COEFFS raw;
        raw.coeff_1 = (real->coeff_1 - 0) / 1;
        raw.coeff_2 = (real->coeff_2 - 0) / 1;
        raw.coeff_3 = (real->coeff_3 - 0) / 1;
        raw.coeff_4 = (real->coeff_4 - 0) / 1;
        raw.coeff_5 = (real->coeff_5 - 0) / 1;
        raw.coeff_6 = (real->coeff_6 - 0) / 1;
        return raw;
    }
    
    inline msg::raw::ALTIMETER_DATA ALTIMETER_DATA_TO_RAW(msg::real::ALTIMETER_DATA* real) {
        msg::raw::ALTIMETER_DATA raw;
        raw.pressure_bar = (real->pressure_bar - 0) / 2.980232238769531e-07;
        raw.temp_celcius = (real->temp_celcius - -40) / 7.450580596923828e-06;
        return raw;
    }
    
    inline msg::raw::HUMIDITY_DATA HUMIDITY_DATA_TO_RAW(msg::real::HUMIDITY_DATA* real) {
        msg::raw::HUMIDITY_DATA raw;
        raw.relative_humidity = (real->relative_humidity - 0) / 0.09765625;
        raw.temp_celcius = (real->temp_celcius - -40) / 0.040283203125;
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
            case msg::id::ALTIMETER_COEFFS:
                dest->ALTIMETER_COEFFS = msg::conv::ALTIMETER_COEFFS_TO_REAL((msg::raw::ALTIMETER_COEFFS*)(raw));
                break;
            case msg::id::ALTIMETER_DATA:
                dest->ALTIMETER_DATA = msg::conv::ALTIMETER_DATA_TO_REAL((msg::raw::ALTIMETER_DATA*)(raw));
                break;
            case msg::id::HUMIDITY_DATA:
                dest->HUMIDITY_DATA = msg::conv::HUMIDITY_DATA_TO_REAL((msg::raw::HUMIDITY_DATA*)(raw));
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
            case msg::id::ALTIMETER_COEFFS:
                dest->ALTIMETER_COEFFS = msg::conv::ALTIMETER_COEFFS_TO_RAW((msg::real::ALTIMETER_COEFFS*)(real));
                break;
            case msg::id::ALTIMETER_DATA:
                dest->ALTIMETER_DATA = msg::conv::ALTIMETER_DATA_TO_RAW((msg::real::ALTIMETER_DATA*)(real));
                break;
            case msg::id::HUMIDITY_DATA:
                dest->HUMIDITY_DATA = msg::conv::HUMIDITY_DATA_TO_RAW((msg::real::HUMIDITY_DATA*)(real));
                break;
        }
        return real->id;
    }
    
    inline void stringifyRealMessage(char* dest, msg::GENERIC_MESSAGE* message) {
        switch(message->id) {
        case msg::id::TEST_MESSAGE:
            sprintf(dest, "%d %.3f \n", 
                    ((msg::real::TEST_MESSAGE*)message)->test, 
                    ((msg::real::TEST_MESSAGE*)message)->VAR2);
            break;
        case msg::id::TEST_MESSAGE_2:
            sprintf(dest, "%d %.3f \n", 
                    ((msg::real::TEST_MESSAGE_2*)message)->VAR1, 
                    ((msg::real::TEST_MESSAGE_2*)message)->VAR2);
            break;
        case msg::id::ALTIMETER_COEFFS:
            sprintf(dest, "%u %u %u %u %u %u \n", 
                    ((msg::real::ALTIMETER_COEFFS*)message)->coeff_1, 
                    ((msg::real::ALTIMETER_COEFFS*)message)->coeff_2, 
                    ((msg::real::ALTIMETER_COEFFS*)message)->coeff_3, 
                    ((msg::real::ALTIMETER_COEFFS*)message)->coeff_4, 
                    ((msg::real::ALTIMETER_COEFFS*)message)->coeff_5, 
                    ((msg::real::ALTIMETER_COEFFS*)message)->coeff_6);
            break;
        case msg::id::ALTIMETER_DATA:
            sprintf(dest, "%.3f %.3f \n", 
                    ((msg::real::ALTIMETER_DATA*)message)->pressure_bar, 
                    ((msg::real::ALTIMETER_DATA*)message)->temp_celcius);
            break;
        case msg::id::HUMIDITY_DATA:
            sprintf(dest, "%.3f %.3f \n", 
                    ((msg::real::HUMIDITY_DATA*)message)->relative_humidity, 
                    ((msg::real::HUMIDITY_DATA*)message)->temp_celcius);
            break;
        }
    }
    
}

