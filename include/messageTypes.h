/* Auto-generated Code from messageGenerator.py */

#pragma once
#include <string.h>
#include <stdio.h>

#define MAX_RAW_MESSAGE_SIZE sizeof(msg::RawMessageUnion)
#define MAX_REAL_MESSAGE_SIZE sizeof(msg::RealMessageUnion)

namespace msg::id {

    enum MessageType {
        TEST_MESSAGE_READ = 0,
        TEST_MESSAGE_WRITE = 1,
        BNO055_PAGE = 2,
        ALTIMETER_COEFFS = 3,
        ALTIMETER_DATA = 4,
        HUMIDITY_DATA = 5,
        BNO055_ACCEL_CONFIG = 6,
        BNO055_GYRO_CONFIG = 7,
        BNO055_MAG_CONFIG = 8,
        BNO055_OPR_MODE = 9,
        BNO055_AXIS_CONFIG = 10,
        BNO055_UNIT_SELECTION = 11,
        BNO055_CAL_ACCEL = 12,
        BNO055_CAL_MAG = 13,
        BNO055_CAL_GYRO = 14,
        BNO055_DATA_ACCEL = 15,
        BNO055_DATA_GYRO = 16,
        BNO055_DATA_MAG = 17,
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

    struct TEST_MESSAGE_READ : GENERIC_MESSAGE {
        TEST_MESSAGE_READ() { id = msg::id::TEST_MESSAGE_READ; size = sizeof(TEST_MESSAGE_READ); }
        int VAR1;
        float VAR2 = 5.2;
    };
    
    struct TEST_MESSAGE_WRITE : GENERIC_MESSAGE {
        TEST_MESSAGE_WRITE() { id = msg::id::TEST_MESSAGE_WRITE; size = sizeof(TEST_MESSAGE_WRITE); }
        int VAR1;
        float VAR2 = 0.23;
    };
    
    struct BNO055_PAGE : GENERIC_MESSAGE {
        BNO055_PAGE() { id = msg::id::BNO055_PAGE; size = sizeof(BNO055_PAGE); }
        int page;
    };
    
    struct ALTIMETER_COEFFS : GENERIC_MESSAGE {
        ALTIMETER_COEFFS() { id = msg::id::ALTIMETER_COEFFS; size = sizeof(ALTIMETER_COEFFS); }
        unsigned short coeff_1;
        unsigned short coeff_2;
        unsigned short coeff_3;
        unsigned short coeff_4;
        unsigned short coeff_5;
        unsigned short coeff_6;
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
    
    struct BNO055_ACCEL_CONFIG : GENERIC_MESSAGE {
        BNO055_ACCEL_CONFIG() { id = msg::id::BNO055_ACCEL_CONFIG; size = sizeof(BNO055_ACCEL_CONFIG); }
        char G_RANGE = 1;
        char SAMPLE_RATE = 3;
        char OPERATION_MODE;
    };
    
    struct BNO055_GYRO_CONFIG : GENERIC_MESSAGE {
        BNO055_GYRO_CONFIG() { id = msg::id::BNO055_GYRO_CONFIG; size = sizeof(BNO055_GYRO_CONFIG); }
        char RANGE;
        char SAMPLE_RATE = 7;
        char OPERATION_MODE;
    };
    
    struct BNO055_MAG_CONFIG : GENERIC_MESSAGE {
        BNO055_MAG_CONFIG() { id = msg::id::BNO055_MAG_CONFIG; size = sizeof(BNO055_MAG_CONFIG); }
        char SAMPLE_RATE = 3;
        char OPERATION_MODE;
    };
    
    struct BNO055_OPR_MODE : GENERIC_MESSAGE {
        BNO055_OPR_MODE() { id = msg::id::BNO055_OPR_MODE; size = sizeof(BNO055_OPR_MODE); }
        char MODE = 8;
    };
    
    struct BNO055_AXIS_CONFIG : GENERIC_MESSAGE {
        BNO055_AXIS_CONFIG() { id = msg::id::BNO055_AXIS_CONFIG; size = sizeof(BNO055_AXIS_CONFIG); }
        char X_MAP;
        char Y_MAP = 1;
        char Z_MAP = 2;
        bool X_SIGN_INVERT;
        bool Y_SIGN_INVERT;
        bool Z_SIGN_INVERT;
    };
    
    struct BNO055_UNIT_SELECTION : GENERIC_MESSAGE {
        BNO055_UNIT_SELECTION() { id = msg::id::BNO055_UNIT_SELECTION; size = sizeof(BNO055_UNIT_SELECTION); }
        char ACCELERATION;
        char ANGULAR_RATE;
        char EULER_ANGLES;
        char TEMPERATURE;
        char FUSION_OUTPUT_FORMAT;
    };
    
    struct BNO055_CAL_ACCEL : GENERIC_MESSAGE {
        BNO055_CAL_ACCEL() { id = msg::id::BNO055_CAL_ACCEL; size = sizeof(BNO055_CAL_ACCEL); }
        int RADIUS;
        int OFFSET_X;
        int OFFSET_Y;
        int OFFSET_Z;
    };
    
    struct BNO055_CAL_MAG : GENERIC_MESSAGE {
        BNO055_CAL_MAG() { id = msg::id::BNO055_CAL_MAG; size = sizeof(BNO055_CAL_MAG); }
        int RADIUS;
        int OFFSET_X;
        int OFFSET_Y;
        int OFFSET_Z;
    };
    
    struct BNO055_CAL_GYRO : GENERIC_MESSAGE {
        BNO055_CAL_GYRO() { id = msg::id::BNO055_CAL_GYRO; size = sizeof(BNO055_CAL_GYRO); }
        int OFFSET_X;
        int OFFSET_Y;
        int OFFSET_Z;
    };
    
    struct BNO055_DATA_ACCEL : GENERIC_MESSAGE {
        BNO055_DATA_ACCEL() { id = msg::id::BNO055_DATA_ACCEL; size = sizeof(BNO055_DATA_ACCEL); }
        int X;
        int Y;
        int Z;
    };
    
    struct BNO055_DATA_GYRO : GENERIC_MESSAGE {
        BNO055_DATA_GYRO() { id = msg::id::BNO055_DATA_GYRO; size = sizeof(BNO055_DATA_GYRO); }
        int X;
        int Y;
        int Z;
    };
    
    struct BNO055_DATA_MAG : GENERIC_MESSAGE {
        BNO055_DATA_MAG() { id = msg::id::BNO055_DATA_MAG; size = sizeof(BNO055_DATA_MAG); }
        int X;
        int Y;
        int Z;
    };
    
}

namespace msg::raw {

    struct TEST_MESSAGE_READ : GENERIC_MESSAGE {
        TEST_MESSAGE_READ() { id = msg::id::TEST_MESSAGE_READ; size = sizeof(TEST_MESSAGE_READ); }
        int VAR1 : 16;
        unsigned int VAR2 : 16;
    };
    
    struct TEST_MESSAGE_WRITE : GENERIC_MESSAGE {
        TEST_MESSAGE_WRITE() { id = msg::id::TEST_MESSAGE_WRITE; size = sizeof(TEST_MESSAGE_WRITE); }
        int VAR1 : 16;
        unsigned int VAR2 : 16;
    };
    
    struct BNO055_PAGE : GENERIC_MESSAGE {
        BNO055_PAGE() { id = msg::id::BNO055_PAGE; size = sizeof(BNO055_PAGE); }
        int page : 1;
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
        unsigned int pressure_bar : 24;
        unsigned int temp_celcius : 24;
    };
    
    struct HUMIDITY_DATA : GENERIC_MESSAGE {
        HUMIDITY_DATA() { id = msg::id::HUMIDITY_DATA; size = sizeof(HUMIDITY_DATA); }
        unsigned int relative_humidity : 10;
        unsigned int temp_celcius : 12;
    };
    
    struct BNO055_ACCEL_CONFIG : GENERIC_MESSAGE {
        BNO055_ACCEL_CONFIG() { id = msg::id::BNO055_ACCEL_CONFIG; size = sizeof(BNO055_ACCEL_CONFIG); }
        int G_RANGE : 2;
        int SAMPLE_RATE : 3;
        int OPERATION_MODE : 3;
    };
    
    struct BNO055_GYRO_CONFIG : GENERIC_MESSAGE {
        BNO055_GYRO_CONFIG() { id = msg::id::BNO055_GYRO_CONFIG; size = sizeof(BNO055_GYRO_CONFIG); }
        int RANGE : 3;
        int SAMPLE_RATE : 3;
        int OPERATION_MODE : 3;
    };
    
    struct BNO055_MAG_CONFIG : GENERIC_MESSAGE {
        BNO055_MAG_CONFIG() { id = msg::id::BNO055_MAG_CONFIG; size = sizeof(BNO055_MAG_CONFIG); }
        int SAMPLE_RATE : 3;
        int OPERATION_MODE : 2;
    };
    
    struct BNO055_OPR_MODE : GENERIC_MESSAGE {
        BNO055_OPR_MODE() { id = msg::id::BNO055_OPR_MODE; size = sizeof(BNO055_OPR_MODE); }
        int MODE : 4;
    };
    
    struct BNO055_AXIS_CONFIG : GENERIC_MESSAGE {
        BNO055_AXIS_CONFIG() { id = msg::id::BNO055_AXIS_CONFIG; size = sizeof(BNO055_AXIS_CONFIG); }
        int X_MAP : 2;
        int Y_MAP : 2;
        int Z_MAP : 2;
        int X_SIGN_INVERT : 1;
        int Y_SIGN_INVERT : 1;
        int Z_SIGN_INVERT : 1;
    };
    
    struct BNO055_UNIT_SELECTION : GENERIC_MESSAGE {
        BNO055_UNIT_SELECTION() { id = msg::id::BNO055_UNIT_SELECTION; size = sizeof(BNO055_UNIT_SELECTION); }
        int ACCELERATION : 1;
        int ANGULAR_RATE : 1;
        int EULER_ANGLES : 1;
        int TEMPERATURE : 1;
        int FUSION_OUTPUT_FORMAT : 1;
    };
    
    struct BNO055_CAL_ACCEL : GENERIC_MESSAGE {
        BNO055_CAL_ACCEL() { id = msg::id::BNO055_CAL_ACCEL; size = sizeof(BNO055_CAL_ACCEL); }
        int RADIUS : 16;
        int OFFSET_X : 16;
        int OFFSET_Y : 16;
        int OFFSET_Z : 16;
    };
    
    struct BNO055_CAL_MAG : GENERIC_MESSAGE {
        BNO055_CAL_MAG() { id = msg::id::BNO055_CAL_MAG; size = sizeof(BNO055_CAL_MAG); }
        int RADIUS : 16;
        int OFFSET_X : 16;
        int OFFSET_Y : 16;
        int OFFSET_Z : 16;
    };
    
    struct BNO055_CAL_GYRO : GENERIC_MESSAGE {
        BNO055_CAL_GYRO() { id = msg::id::BNO055_CAL_GYRO; size = sizeof(BNO055_CAL_GYRO); }
        int OFFSET_X : 16;
        int OFFSET_Y : 16;
        int OFFSET_Z : 16;
    };
    
    struct BNO055_DATA_ACCEL : GENERIC_MESSAGE {
        BNO055_DATA_ACCEL() { id = msg::id::BNO055_DATA_ACCEL; size = sizeof(BNO055_DATA_ACCEL); }
        int X : 16;
        int Y : 16;
        int Z : 16;
    };
    
    struct BNO055_DATA_GYRO : GENERIC_MESSAGE {
        BNO055_DATA_GYRO() { id = msg::id::BNO055_DATA_GYRO; size = sizeof(BNO055_DATA_GYRO); }
        int X : 16;
        int Y : 16;
        int Z : 16;
    };
    
    struct BNO055_DATA_MAG : GENERIC_MESSAGE {
        BNO055_DATA_MAG() { id = msg::id::BNO055_DATA_MAG; size = sizeof(BNO055_DATA_MAG); }
        int X : 16;
        int Y : 16;
        int Z : 16;
    };
    
}

namespace msg {

    const int RAW_MESSAGE_SIZES[] = {
        sizeof(msg::raw::TEST_MESSAGE_READ),
        sizeof(msg::raw::TEST_MESSAGE_WRITE),
        sizeof(msg::raw::BNO055_PAGE),
        sizeof(msg::raw::ALTIMETER_COEFFS),
        sizeof(msg::raw::ALTIMETER_DATA),
        sizeof(msg::raw::HUMIDITY_DATA),
        sizeof(msg::raw::BNO055_ACCEL_CONFIG),
        sizeof(msg::raw::BNO055_GYRO_CONFIG),
        sizeof(msg::raw::BNO055_MAG_CONFIG),
        sizeof(msg::raw::BNO055_OPR_MODE),
        sizeof(msg::raw::BNO055_AXIS_CONFIG),
        sizeof(msg::raw::BNO055_UNIT_SELECTION),
        sizeof(msg::raw::BNO055_CAL_ACCEL),
        sizeof(msg::raw::BNO055_CAL_MAG),
        sizeof(msg::raw::BNO055_CAL_GYRO),
        sizeof(msg::raw::BNO055_DATA_ACCEL),
        sizeof(msg::raw::BNO055_DATA_GYRO),
        sizeof(msg::raw::BNO055_DATA_MAG),
    };
    
    const int REAL_MESSAGE_SIZES[] = {
        sizeof(msg::real::TEST_MESSAGE_READ),
        sizeof(msg::real::TEST_MESSAGE_WRITE),
        sizeof(msg::real::BNO055_PAGE),
        sizeof(msg::real::ALTIMETER_COEFFS),
        sizeof(msg::real::ALTIMETER_DATA),
        sizeof(msg::real::HUMIDITY_DATA),
        sizeof(msg::real::BNO055_ACCEL_CONFIG),
        sizeof(msg::real::BNO055_GYRO_CONFIG),
        sizeof(msg::real::BNO055_MAG_CONFIG),
        sizeof(msg::real::BNO055_OPR_MODE),
        sizeof(msg::real::BNO055_AXIS_CONFIG),
        sizeof(msg::real::BNO055_UNIT_SELECTION),
        sizeof(msg::real::BNO055_CAL_ACCEL),
        sizeof(msg::real::BNO055_CAL_MAG),
        sizeof(msg::real::BNO055_CAL_GYRO),
        sizeof(msg::real::BNO055_DATA_ACCEL),
        sizeof(msg::real::BNO055_DATA_GYRO),
        sizeof(msg::real::BNO055_DATA_MAG),
    };
    
    static const char* messageNames[] = {
        "TEST_MESSAGE_READ",
        "TEST_MESSAGE_WRITE",
        "BNO055_PAGE",
        "ALTIMETER_COEFFS",
        "ALTIMETER_DATA",
        "HUMIDITY_DATA",
        "BNO055_ACCEL_CONFIG",
        "BNO055_GYRO_CONFIG",
        "BNO055_MAG_CONFIG",
        "BNO055_OPR_MODE",
        "BNO055_AXIS_CONFIG",
        "BNO055_UNIT_SELECTION",
        "BNO055_CAL_ACCEL",
        "BNO055_CAL_MAG",
        "BNO055_CAL_GYRO",
        "BNO055_DATA_ACCEL",
        "BNO055_DATA_GYRO",
        "BNO055_DATA_MAG",
    };
    
    struct MessageCollection {
        real::TEST_MESSAGE_READ TEST_MESSAGE_READ;
        real::TEST_MESSAGE_WRITE TEST_MESSAGE_WRITE;
        real::BNO055_PAGE BNO055_PAGE;
        real::ALTIMETER_COEFFS ALTIMETER_COEFFS;
        real::ALTIMETER_DATA ALTIMETER_DATA;
        real::HUMIDITY_DATA HUMIDITY_DATA;
        real::BNO055_ACCEL_CONFIG BNO055_ACCEL_CONFIG;
        real::BNO055_GYRO_CONFIG BNO055_GYRO_CONFIG;
        real::BNO055_MAG_CONFIG BNO055_MAG_CONFIG;
        real::BNO055_OPR_MODE BNO055_OPR_MODE;
        real::BNO055_AXIS_CONFIG BNO055_AXIS_CONFIG;
        real::BNO055_UNIT_SELECTION BNO055_UNIT_SELECTION;
        real::BNO055_CAL_ACCEL BNO055_CAL_ACCEL;
        real::BNO055_CAL_MAG BNO055_CAL_MAG;
        real::BNO055_CAL_GYRO BNO055_CAL_GYRO;
        real::BNO055_DATA_ACCEL BNO055_DATA_ACCEL;
        real::BNO055_DATA_GYRO BNO055_DATA_GYRO;
        real::BNO055_DATA_MAG BNO055_DATA_MAG;
    };
    
    union RealMessageUnion {
        RealMessageUnion() { memset( this, 0, sizeof( RealMessageUnion ) ); }
        real::TEST_MESSAGE_READ TEST_MESSAGE_READ;
        real::TEST_MESSAGE_WRITE TEST_MESSAGE_WRITE;
        real::BNO055_PAGE BNO055_PAGE;
        real::ALTIMETER_COEFFS ALTIMETER_COEFFS;
        real::ALTIMETER_DATA ALTIMETER_DATA;
        real::HUMIDITY_DATA HUMIDITY_DATA;
        real::BNO055_ACCEL_CONFIG BNO055_ACCEL_CONFIG;
        real::BNO055_GYRO_CONFIG BNO055_GYRO_CONFIG;
        real::BNO055_MAG_CONFIG BNO055_MAG_CONFIG;
        real::BNO055_OPR_MODE BNO055_OPR_MODE;
        real::BNO055_AXIS_CONFIG BNO055_AXIS_CONFIG;
        real::BNO055_UNIT_SELECTION BNO055_UNIT_SELECTION;
        real::BNO055_CAL_ACCEL BNO055_CAL_ACCEL;
        real::BNO055_CAL_MAG BNO055_CAL_MAG;
        real::BNO055_CAL_GYRO BNO055_CAL_GYRO;
        real::BNO055_DATA_ACCEL BNO055_DATA_ACCEL;
        real::BNO055_DATA_GYRO BNO055_DATA_GYRO;
        real::BNO055_DATA_MAG BNO055_DATA_MAG;
    };
    
    union RawMessageUnion {
        RawMessageUnion() { memset( this, 0, sizeof( RawMessageUnion ) ); }
        raw::TEST_MESSAGE_READ TEST_MESSAGE_READ;
        raw::TEST_MESSAGE_WRITE TEST_MESSAGE_WRITE;
        raw::BNO055_PAGE BNO055_PAGE;
        raw::ALTIMETER_COEFFS ALTIMETER_COEFFS;
        raw::ALTIMETER_DATA ALTIMETER_DATA;
        raw::HUMIDITY_DATA HUMIDITY_DATA;
        raw::BNO055_ACCEL_CONFIG BNO055_ACCEL_CONFIG;
        raw::BNO055_GYRO_CONFIG BNO055_GYRO_CONFIG;
        raw::BNO055_MAG_CONFIG BNO055_MAG_CONFIG;
        raw::BNO055_OPR_MODE BNO055_OPR_MODE;
        raw::BNO055_AXIS_CONFIG BNO055_AXIS_CONFIG;
        raw::BNO055_UNIT_SELECTION BNO055_UNIT_SELECTION;
        raw::BNO055_CAL_ACCEL BNO055_CAL_ACCEL;
        raw::BNO055_CAL_MAG BNO055_CAL_MAG;
        raw::BNO055_CAL_GYRO BNO055_CAL_GYRO;
        raw::BNO055_DATA_ACCEL BNO055_DATA_ACCEL;
        raw::BNO055_DATA_GYRO BNO055_DATA_GYRO;
        raw::BNO055_DATA_MAG BNO055_DATA_MAG;
    };
    
    inline void* getMessageAddressFromCollection(MessageCollection& collection, const id::MessageType type) {
        switch (type) {
            case msg::id::TEST_MESSAGE_READ:
                return &collection.TEST_MESSAGE_READ;
            case msg::id::TEST_MESSAGE_WRITE:
                return &collection.TEST_MESSAGE_WRITE;
            case msg::id::BNO055_PAGE:
                return &collection.BNO055_PAGE;
            case msg::id::ALTIMETER_COEFFS:
                return &collection.ALTIMETER_COEFFS;
            case msg::id::ALTIMETER_DATA:
                return &collection.ALTIMETER_DATA;
            case msg::id::HUMIDITY_DATA:
                return &collection.HUMIDITY_DATA;
            case msg::id::BNO055_ACCEL_CONFIG:
                return &collection.BNO055_ACCEL_CONFIG;
            case msg::id::BNO055_GYRO_CONFIG:
                return &collection.BNO055_GYRO_CONFIG;
            case msg::id::BNO055_MAG_CONFIG:
                return &collection.BNO055_MAG_CONFIG;
            case msg::id::BNO055_OPR_MODE:
                return &collection.BNO055_OPR_MODE;
            case msg::id::BNO055_AXIS_CONFIG:
                return &collection.BNO055_AXIS_CONFIG;
            case msg::id::BNO055_UNIT_SELECTION:
                return &collection.BNO055_UNIT_SELECTION;
            case msg::id::BNO055_CAL_ACCEL:
                return &collection.BNO055_CAL_ACCEL;
            case msg::id::BNO055_CAL_MAG:
                return &collection.BNO055_CAL_MAG;
            case msg::id::BNO055_CAL_GYRO:
                return &collection.BNO055_CAL_GYRO;
            case msg::id::BNO055_DATA_ACCEL:
                return &collection.BNO055_DATA_ACCEL;
            case msg::id::BNO055_DATA_GYRO:
                return &collection.BNO055_DATA_GYRO;
            case msg::id::BNO055_DATA_MAG:
                return &collection.BNO055_DATA_MAG;
            default:
                return nullptr;
        }
    }
    
}

namespace msg::conv {

    inline msg::real::TEST_MESSAGE_READ TEST_MESSAGE_READ_TO_REAL(msg::raw::TEST_MESSAGE_READ* raw) {
        msg::real::TEST_MESSAGE_READ real;
        real.VAR1 = (raw->VAR1);
        real.VAR2 = (raw->VAR2 * 0.00152587890625) + 0;
        return real;
    }
    
    inline msg::real::TEST_MESSAGE_WRITE TEST_MESSAGE_WRITE_TO_REAL(msg::raw::TEST_MESSAGE_WRITE* raw) {
        msg::real::TEST_MESSAGE_WRITE real;
        real.VAR1 = (raw->VAR1);
        real.VAR2 = (raw->VAR2 * 0.0030517578125) + 0;
        return real;
    }
    
    inline msg::real::BNO055_PAGE BNO055_PAGE_TO_REAL(msg::raw::BNO055_PAGE* raw) {
        msg::real::BNO055_PAGE real;
        real.page = (raw->page);
        return real;
    }
    
    inline msg::real::ALTIMETER_COEFFS ALTIMETER_COEFFS_TO_REAL(msg::raw::ALTIMETER_COEFFS* raw) {
        msg::real::ALTIMETER_COEFFS real;
        real.coeff_1 = (raw->coeff_1);
        real.coeff_2 = (raw->coeff_2);
        real.coeff_3 = (raw->coeff_3);
        real.coeff_4 = (raw->coeff_4);
        real.coeff_5 = (raw->coeff_5);
        real.coeff_6 = (raw->coeff_6);
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
    
    inline msg::real::BNO055_ACCEL_CONFIG BNO055_ACCEL_CONFIG_TO_REAL(msg::raw::BNO055_ACCEL_CONFIG* raw) {
        msg::real::BNO055_ACCEL_CONFIG real;
        real.G_RANGE = (raw->G_RANGE);
        real.SAMPLE_RATE = (raw->SAMPLE_RATE);
        real.OPERATION_MODE = (raw->OPERATION_MODE);
        return real;
    }
    
    inline msg::real::BNO055_GYRO_CONFIG BNO055_GYRO_CONFIG_TO_REAL(msg::raw::BNO055_GYRO_CONFIG* raw) {
        msg::real::BNO055_GYRO_CONFIG real;
        real.RANGE = (raw->RANGE);
        real.SAMPLE_RATE = (raw->SAMPLE_RATE);
        real.OPERATION_MODE = (raw->OPERATION_MODE);
        return real;
    }
    
    inline msg::real::BNO055_MAG_CONFIG BNO055_MAG_CONFIG_TO_REAL(msg::raw::BNO055_MAG_CONFIG* raw) {
        msg::real::BNO055_MAG_CONFIG real;
        real.SAMPLE_RATE = (raw->SAMPLE_RATE);
        real.OPERATION_MODE = (raw->OPERATION_MODE);
        return real;
    }
    
    inline msg::real::BNO055_OPR_MODE BNO055_OPR_MODE_TO_REAL(msg::raw::BNO055_OPR_MODE* raw) {
        msg::real::BNO055_OPR_MODE real;
        real.MODE = (raw->MODE);
        return real;
    }
    
    inline msg::real::BNO055_AXIS_CONFIG BNO055_AXIS_CONFIG_TO_REAL(msg::raw::BNO055_AXIS_CONFIG* raw) {
        msg::real::BNO055_AXIS_CONFIG real;
        real.X_MAP = (raw->X_MAP);
        real.Y_MAP = (raw->Y_MAP);
        real.Z_MAP = (raw->Z_MAP);
        real.X_SIGN_INVERT = (raw->X_SIGN_INVERT);
        real.Y_SIGN_INVERT = (raw->Y_SIGN_INVERT);
        real.Z_SIGN_INVERT = (raw->Z_SIGN_INVERT);
        return real;
    }
    
    inline msg::real::BNO055_UNIT_SELECTION BNO055_UNIT_SELECTION_TO_REAL(msg::raw::BNO055_UNIT_SELECTION* raw) {
        msg::real::BNO055_UNIT_SELECTION real;
        real.ACCELERATION = (raw->ACCELERATION);
        real.ANGULAR_RATE = (raw->ANGULAR_RATE);
        real.EULER_ANGLES = (raw->EULER_ANGLES);
        real.TEMPERATURE = (raw->TEMPERATURE);
        real.FUSION_OUTPUT_FORMAT = (raw->FUSION_OUTPUT_FORMAT);
        return real;
    }
    
    inline msg::real::BNO055_CAL_ACCEL BNO055_CAL_ACCEL_TO_REAL(msg::raw::BNO055_CAL_ACCEL* raw) {
        msg::real::BNO055_CAL_ACCEL real;
        real.RADIUS = (raw->RADIUS);
        real.OFFSET_X = (raw->OFFSET_X);
        real.OFFSET_Y = (raw->OFFSET_Y);
        real.OFFSET_Z = (raw->OFFSET_Z);
        return real;
    }
    
    inline msg::real::BNO055_CAL_MAG BNO055_CAL_MAG_TO_REAL(msg::raw::BNO055_CAL_MAG* raw) {
        msg::real::BNO055_CAL_MAG real;
        real.RADIUS = (raw->RADIUS);
        real.OFFSET_X = (raw->OFFSET_X);
        real.OFFSET_Y = (raw->OFFSET_Y);
        real.OFFSET_Z = (raw->OFFSET_Z);
        return real;
    }
    
    inline msg::real::BNO055_CAL_GYRO BNO055_CAL_GYRO_TO_REAL(msg::raw::BNO055_CAL_GYRO* raw) {
        msg::real::BNO055_CAL_GYRO real;
        real.OFFSET_X = (raw->OFFSET_X);
        real.OFFSET_Y = (raw->OFFSET_Y);
        real.OFFSET_Z = (raw->OFFSET_Z);
        return real;
    }
    
    inline msg::real::BNO055_DATA_ACCEL BNO055_DATA_ACCEL_TO_REAL(msg::raw::BNO055_DATA_ACCEL* raw) {
        msg::real::BNO055_DATA_ACCEL real;
        real.X = (raw->X);
        real.Y = (raw->Y);
        real.Z = (raw->Z);
        return real;
    }
    
    inline msg::real::BNO055_DATA_GYRO BNO055_DATA_GYRO_TO_REAL(msg::raw::BNO055_DATA_GYRO* raw) {
        msg::real::BNO055_DATA_GYRO real;
        real.X = (raw->X);
        real.Y = (raw->Y);
        real.Z = (raw->Z);
        return real;
    }
    
    inline msg::real::BNO055_DATA_MAG BNO055_DATA_MAG_TO_REAL(msg::raw::BNO055_DATA_MAG* raw) {
        msg::real::BNO055_DATA_MAG real;
        real.X = (raw->X);
        real.Y = (raw->Y);
        real.Z = (raw->Z);
        return real;
    }
    
    inline msg::raw::TEST_MESSAGE_READ TEST_MESSAGE_READ_TO_RAW(msg::real::TEST_MESSAGE_READ* real) {
        msg::raw::TEST_MESSAGE_READ raw;
        raw.VAR1 = (real->VAR1);
        raw.VAR2 = (real->VAR2 - 0) / 0.00152587890625;
        return raw;
    }
    
    inline msg::raw::TEST_MESSAGE_WRITE TEST_MESSAGE_WRITE_TO_RAW(msg::real::TEST_MESSAGE_WRITE* real) {
        msg::raw::TEST_MESSAGE_WRITE raw;
        raw.VAR1 = (real->VAR1);
        raw.VAR2 = (real->VAR2 - 0) / 0.0030517578125;
        return raw;
    }
    
    inline msg::raw::BNO055_PAGE BNO055_PAGE_TO_RAW(msg::real::BNO055_PAGE* real) {
        msg::raw::BNO055_PAGE raw;
        raw.page = (real->page);
        return raw;
    }
    
    inline msg::raw::ALTIMETER_COEFFS ALTIMETER_COEFFS_TO_RAW(msg::real::ALTIMETER_COEFFS* real) {
        msg::raw::ALTIMETER_COEFFS raw;
        raw.coeff_1 = (real->coeff_1);
        raw.coeff_2 = (real->coeff_2);
        raw.coeff_3 = (real->coeff_3);
        raw.coeff_4 = (real->coeff_4);
        raw.coeff_5 = (real->coeff_5);
        raw.coeff_6 = (real->coeff_6);
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
    
    inline msg::raw::BNO055_ACCEL_CONFIG BNO055_ACCEL_CONFIG_TO_RAW(msg::real::BNO055_ACCEL_CONFIG* real) {
        msg::raw::BNO055_ACCEL_CONFIG raw;
        raw.G_RANGE = (real->G_RANGE);
        raw.SAMPLE_RATE = (real->SAMPLE_RATE);
        raw.OPERATION_MODE = (real->OPERATION_MODE);
        return raw;
    }
    
    inline msg::raw::BNO055_GYRO_CONFIG BNO055_GYRO_CONFIG_TO_RAW(msg::real::BNO055_GYRO_CONFIG* real) {
        msg::raw::BNO055_GYRO_CONFIG raw;
        raw.RANGE = (real->RANGE);
        raw.SAMPLE_RATE = (real->SAMPLE_RATE);
        raw.OPERATION_MODE = (real->OPERATION_MODE);
        return raw;
    }
    
    inline msg::raw::BNO055_MAG_CONFIG BNO055_MAG_CONFIG_TO_RAW(msg::real::BNO055_MAG_CONFIG* real) {
        msg::raw::BNO055_MAG_CONFIG raw;
        raw.SAMPLE_RATE = (real->SAMPLE_RATE);
        raw.OPERATION_MODE = (real->OPERATION_MODE);
        return raw;
    }
    
    inline msg::raw::BNO055_OPR_MODE BNO055_OPR_MODE_TO_RAW(msg::real::BNO055_OPR_MODE* real) {
        msg::raw::BNO055_OPR_MODE raw;
        raw.MODE = (real->MODE);
        return raw;
    }
    
    inline msg::raw::BNO055_AXIS_CONFIG BNO055_AXIS_CONFIG_TO_RAW(msg::real::BNO055_AXIS_CONFIG* real) {
        msg::raw::BNO055_AXIS_CONFIG raw;
        raw.X_MAP = (real->X_MAP);
        raw.Y_MAP = (real->Y_MAP);
        raw.Z_MAP = (real->Z_MAP);
        raw.X_SIGN_INVERT = (real->X_SIGN_INVERT);
        raw.Y_SIGN_INVERT = (real->Y_SIGN_INVERT);
        raw.Z_SIGN_INVERT = (real->Z_SIGN_INVERT);
        return raw;
    }
    
    inline msg::raw::BNO055_UNIT_SELECTION BNO055_UNIT_SELECTION_TO_RAW(msg::real::BNO055_UNIT_SELECTION* real) {
        msg::raw::BNO055_UNIT_SELECTION raw;
        raw.ACCELERATION = (real->ACCELERATION);
        raw.ANGULAR_RATE = (real->ANGULAR_RATE);
        raw.EULER_ANGLES = (real->EULER_ANGLES);
        raw.TEMPERATURE = (real->TEMPERATURE);
        raw.FUSION_OUTPUT_FORMAT = (real->FUSION_OUTPUT_FORMAT);
        return raw;
    }
    
    inline msg::raw::BNO055_CAL_ACCEL BNO055_CAL_ACCEL_TO_RAW(msg::real::BNO055_CAL_ACCEL* real) {
        msg::raw::BNO055_CAL_ACCEL raw;
        raw.RADIUS = (real->RADIUS);
        raw.OFFSET_X = (real->OFFSET_X);
        raw.OFFSET_Y = (real->OFFSET_Y);
        raw.OFFSET_Z = (real->OFFSET_Z);
        return raw;
    }
    
    inline msg::raw::BNO055_CAL_MAG BNO055_CAL_MAG_TO_RAW(msg::real::BNO055_CAL_MAG* real) {
        msg::raw::BNO055_CAL_MAG raw;
        raw.RADIUS = (real->RADIUS);
        raw.OFFSET_X = (real->OFFSET_X);
        raw.OFFSET_Y = (real->OFFSET_Y);
        raw.OFFSET_Z = (real->OFFSET_Z);
        return raw;
    }
    
    inline msg::raw::BNO055_CAL_GYRO BNO055_CAL_GYRO_TO_RAW(msg::real::BNO055_CAL_GYRO* real) {
        msg::raw::BNO055_CAL_GYRO raw;
        raw.OFFSET_X = (real->OFFSET_X);
        raw.OFFSET_Y = (real->OFFSET_Y);
        raw.OFFSET_Z = (real->OFFSET_Z);
        return raw;
    }
    
    inline msg::raw::BNO055_DATA_ACCEL BNO055_DATA_ACCEL_TO_RAW(msg::real::BNO055_DATA_ACCEL* real) {
        msg::raw::BNO055_DATA_ACCEL raw;
        raw.X = (real->X);
        raw.Y = (real->Y);
        raw.Z = (real->Z);
        return raw;
    }
    
    inline msg::raw::BNO055_DATA_GYRO BNO055_DATA_GYRO_TO_RAW(msg::real::BNO055_DATA_GYRO* real) {
        msg::raw::BNO055_DATA_GYRO raw;
        raw.X = (real->X);
        raw.Y = (real->Y);
        raw.Z = (real->Z);
        return raw;
    }
    
    inline msg::raw::BNO055_DATA_MAG BNO055_DATA_MAG_TO_RAW(msg::real::BNO055_DATA_MAG* real) {
        msg::raw::BNO055_DATA_MAG raw;
        raw.X = (real->X);
        raw.Y = (real->Y);
        raw.Z = (real->Z);
        return raw;
    }
    
    inline msg::id::MessageType convertRawToReal(msg::RealMessageUnion* dest, GENERIC_MESSAGE* raw) {
        switch(raw->id) {
            case msg::id::TEST_MESSAGE_READ:
                dest->TEST_MESSAGE_READ = msg::conv::TEST_MESSAGE_READ_TO_REAL((msg::raw::TEST_MESSAGE_READ*)(raw));
                break;
            case msg::id::TEST_MESSAGE_WRITE:
                dest->TEST_MESSAGE_WRITE = msg::conv::TEST_MESSAGE_WRITE_TO_REAL((msg::raw::TEST_MESSAGE_WRITE*)(raw));
                break;
            case msg::id::BNO055_PAGE:
                dest->BNO055_PAGE = msg::conv::BNO055_PAGE_TO_REAL((msg::raw::BNO055_PAGE*)(raw));
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
            case msg::id::BNO055_ACCEL_CONFIG:
                dest->BNO055_ACCEL_CONFIG = msg::conv::BNO055_ACCEL_CONFIG_TO_REAL((msg::raw::BNO055_ACCEL_CONFIG*)(raw));
                break;
            case msg::id::BNO055_GYRO_CONFIG:
                dest->BNO055_GYRO_CONFIG = msg::conv::BNO055_GYRO_CONFIG_TO_REAL((msg::raw::BNO055_GYRO_CONFIG*)(raw));
                break;
            case msg::id::BNO055_MAG_CONFIG:
                dest->BNO055_MAG_CONFIG = msg::conv::BNO055_MAG_CONFIG_TO_REAL((msg::raw::BNO055_MAG_CONFIG*)(raw));
                break;
            case msg::id::BNO055_OPR_MODE:
                dest->BNO055_OPR_MODE = msg::conv::BNO055_OPR_MODE_TO_REAL((msg::raw::BNO055_OPR_MODE*)(raw));
                break;
            case msg::id::BNO055_AXIS_CONFIG:
                dest->BNO055_AXIS_CONFIG = msg::conv::BNO055_AXIS_CONFIG_TO_REAL((msg::raw::BNO055_AXIS_CONFIG*)(raw));
                break;
            case msg::id::BNO055_UNIT_SELECTION:
                dest->BNO055_UNIT_SELECTION = msg::conv::BNO055_UNIT_SELECTION_TO_REAL((msg::raw::BNO055_UNIT_SELECTION*)(raw));
                break;
            case msg::id::BNO055_CAL_ACCEL:
                dest->BNO055_CAL_ACCEL = msg::conv::BNO055_CAL_ACCEL_TO_REAL((msg::raw::BNO055_CAL_ACCEL*)(raw));
                break;
            case msg::id::BNO055_CAL_MAG:
                dest->BNO055_CAL_MAG = msg::conv::BNO055_CAL_MAG_TO_REAL((msg::raw::BNO055_CAL_MAG*)(raw));
                break;
            case msg::id::BNO055_CAL_GYRO:
                dest->BNO055_CAL_GYRO = msg::conv::BNO055_CAL_GYRO_TO_REAL((msg::raw::BNO055_CAL_GYRO*)(raw));
                break;
            case msg::id::BNO055_DATA_ACCEL:
                dest->BNO055_DATA_ACCEL = msg::conv::BNO055_DATA_ACCEL_TO_REAL((msg::raw::BNO055_DATA_ACCEL*)(raw));
                break;
            case msg::id::BNO055_DATA_GYRO:
                dest->BNO055_DATA_GYRO = msg::conv::BNO055_DATA_GYRO_TO_REAL((msg::raw::BNO055_DATA_GYRO*)(raw));
                break;
            case msg::id::BNO055_DATA_MAG:
                dest->BNO055_DATA_MAG = msg::conv::BNO055_DATA_MAG_TO_REAL((msg::raw::BNO055_DATA_MAG*)(raw));
                break;
        }
        return raw->id;
    }
    
    inline msg::id::MessageType convertRealToRaw(msg::RawMessageUnion* dest, GENERIC_MESSAGE* real) {
        switch(real->id) {
            case msg::id::TEST_MESSAGE_READ:
                dest->TEST_MESSAGE_READ = msg::conv::TEST_MESSAGE_READ_TO_RAW((msg::real::TEST_MESSAGE_READ*)(real));
                break;
            case msg::id::TEST_MESSAGE_WRITE:
                dest->TEST_MESSAGE_WRITE = msg::conv::TEST_MESSAGE_WRITE_TO_RAW((msg::real::TEST_MESSAGE_WRITE*)(real));
                break;
            case msg::id::BNO055_PAGE:
                dest->BNO055_PAGE = msg::conv::BNO055_PAGE_TO_RAW((msg::real::BNO055_PAGE*)(real));
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
            case msg::id::BNO055_ACCEL_CONFIG:
                dest->BNO055_ACCEL_CONFIG = msg::conv::BNO055_ACCEL_CONFIG_TO_RAW((msg::real::BNO055_ACCEL_CONFIG*)(real));
                break;
            case msg::id::BNO055_GYRO_CONFIG:
                dest->BNO055_GYRO_CONFIG = msg::conv::BNO055_GYRO_CONFIG_TO_RAW((msg::real::BNO055_GYRO_CONFIG*)(real));
                break;
            case msg::id::BNO055_MAG_CONFIG:
                dest->BNO055_MAG_CONFIG = msg::conv::BNO055_MAG_CONFIG_TO_RAW((msg::real::BNO055_MAG_CONFIG*)(real));
                break;
            case msg::id::BNO055_OPR_MODE:
                dest->BNO055_OPR_MODE = msg::conv::BNO055_OPR_MODE_TO_RAW((msg::real::BNO055_OPR_MODE*)(real));
                break;
            case msg::id::BNO055_AXIS_CONFIG:
                dest->BNO055_AXIS_CONFIG = msg::conv::BNO055_AXIS_CONFIG_TO_RAW((msg::real::BNO055_AXIS_CONFIG*)(real));
                break;
            case msg::id::BNO055_UNIT_SELECTION:
                dest->BNO055_UNIT_SELECTION = msg::conv::BNO055_UNIT_SELECTION_TO_RAW((msg::real::BNO055_UNIT_SELECTION*)(real));
                break;
            case msg::id::BNO055_CAL_ACCEL:
                dest->BNO055_CAL_ACCEL = msg::conv::BNO055_CAL_ACCEL_TO_RAW((msg::real::BNO055_CAL_ACCEL*)(real));
                break;
            case msg::id::BNO055_CAL_MAG:
                dest->BNO055_CAL_MAG = msg::conv::BNO055_CAL_MAG_TO_RAW((msg::real::BNO055_CAL_MAG*)(real));
                break;
            case msg::id::BNO055_CAL_GYRO:
                dest->BNO055_CAL_GYRO = msg::conv::BNO055_CAL_GYRO_TO_RAW((msg::real::BNO055_CAL_GYRO*)(real));
                break;
            case msg::id::BNO055_DATA_ACCEL:
                dest->BNO055_DATA_ACCEL = msg::conv::BNO055_DATA_ACCEL_TO_RAW((msg::real::BNO055_DATA_ACCEL*)(real));
                break;
            case msg::id::BNO055_DATA_GYRO:
                dest->BNO055_DATA_GYRO = msg::conv::BNO055_DATA_GYRO_TO_RAW((msg::real::BNO055_DATA_GYRO*)(real));
                break;
            case msg::id::BNO055_DATA_MAG:
                dest->BNO055_DATA_MAG = msg::conv::BNO055_DATA_MAG_TO_RAW((msg::real::BNO055_DATA_MAG*)(real));
                break;
        }
        return real->id;
    }
    
    inline void stringifyRealMessage(char* dest, msg::GENERIC_MESSAGE* message) {
        switch(message->id) {
        case msg::id::TEST_MESSAGE_READ:
            sprintf(dest, "%d %.3f \n", 
                    ((msg::real::TEST_MESSAGE_READ*)message)->VAR1, 
                    ((msg::real::TEST_MESSAGE_READ*)message)->VAR2);
            break;
        case msg::id::TEST_MESSAGE_WRITE:
            sprintf(dest, "%d %.3f \n", 
                    ((msg::real::TEST_MESSAGE_WRITE*)message)->VAR1, 
                    ((msg::real::TEST_MESSAGE_WRITE*)message)->VAR2);
            break;
        case msg::id::BNO055_PAGE:
            sprintf(dest, "%d \n", 
                    ((msg::real::BNO055_PAGE*)message)->page);
            break;
        case msg::id::ALTIMETER_COEFFS:
            sprintf(dest, "%hu %hu %hu %hu %hu %hu \n", 
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
        case msg::id::BNO055_ACCEL_CONFIG:
            sprintf(dest, "%d %d %d \n", 
                    ((msg::real::BNO055_ACCEL_CONFIG*)message)->G_RANGE, 
                    ((msg::real::BNO055_ACCEL_CONFIG*)message)->SAMPLE_RATE, 
                    ((msg::real::BNO055_ACCEL_CONFIG*)message)->OPERATION_MODE);
            break;
        case msg::id::BNO055_GYRO_CONFIG:
            sprintf(dest, "%d %d %d \n", 
                    ((msg::real::BNO055_GYRO_CONFIG*)message)->RANGE, 
                    ((msg::real::BNO055_GYRO_CONFIG*)message)->SAMPLE_RATE, 
                    ((msg::real::BNO055_GYRO_CONFIG*)message)->OPERATION_MODE);
            break;
        case msg::id::BNO055_MAG_CONFIG:
            sprintf(dest, "%d %d \n", 
                    ((msg::real::BNO055_MAG_CONFIG*)message)->SAMPLE_RATE, 
                    ((msg::real::BNO055_MAG_CONFIG*)message)->OPERATION_MODE);
            break;
        case msg::id::BNO055_OPR_MODE:
            sprintf(dest, "%d \n", 
                    ((msg::real::BNO055_OPR_MODE*)message)->MODE);
            break;
        case msg::id::BNO055_AXIS_CONFIG:
            sprintf(dest, "%d %d %d %d %d %d \n", 
                    ((msg::real::BNO055_AXIS_CONFIG*)message)->X_MAP, 
                    ((msg::real::BNO055_AXIS_CONFIG*)message)->Y_MAP, 
                    ((msg::real::BNO055_AXIS_CONFIG*)message)->Z_MAP, 
                    ((msg::real::BNO055_AXIS_CONFIG*)message)->X_SIGN_INVERT, 
                    ((msg::real::BNO055_AXIS_CONFIG*)message)->Y_SIGN_INVERT, 
                    ((msg::real::BNO055_AXIS_CONFIG*)message)->Z_SIGN_INVERT);
            break;
        case msg::id::BNO055_UNIT_SELECTION:
            sprintf(dest, "%d %d %d %d %d \n", 
                    ((msg::real::BNO055_UNIT_SELECTION*)message)->ACCELERATION, 
                    ((msg::real::BNO055_UNIT_SELECTION*)message)->ANGULAR_RATE, 
                    ((msg::real::BNO055_UNIT_SELECTION*)message)->EULER_ANGLES, 
                    ((msg::real::BNO055_UNIT_SELECTION*)message)->TEMPERATURE, 
                    ((msg::real::BNO055_UNIT_SELECTION*)message)->FUSION_OUTPUT_FORMAT);
            break;
        case msg::id::BNO055_CAL_ACCEL:
            sprintf(dest, "%d %d %d %d \n", 
                    ((msg::real::BNO055_CAL_ACCEL*)message)->RADIUS, 
                    ((msg::real::BNO055_CAL_ACCEL*)message)->OFFSET_X, 
                    ((msg::real::BNO055_CAL_ACCEL*)message)->OFFSET_Y, 
                    ((msg::real::BNO055_CAL_ACCEL*)message)->OFFSET_Z);
            break;
        case msg::id::BNO055_CAL_MAG:
            sprintf(dest, "%d %d %d %d \n", 
                    ((msg::real::BNO055_CAL_MAG*)message)->RADIUS, 
                    ((msg::real::BNO055_CAL_MAG*)message)->OFFSET_X, 
                    ((msg::real::BNO055_CAL_MAG*)message)->OFFSET_Y, 
                    ((msg::real::BNO055_CAL_MAG*)message)->OFFSET_Z);
            break;
        case msg::id::BNO055_CAL_GYRO:
            sprintf(dest, "%d %d %d \n", 
                    ((msg::real::BNO055_CAL_GYRO*)message)->OFFSET_X, 
                    ((msg::real::BNO055_CAL_GYRO*)message)->OFFSET_Y, 
                    ((msg::real::BNO055_CAL_GYRO*)message)->OFFSET_Z);
            break;
        case msg::id::BNO055_DATA_ACCEL:
            sprintf(dest, "%d %d %d \n", 
                    ((msg::real::BNO055_DATA_ACCEL*)message)->X, 
                    ((msg::real::BNO055_DATA_ACCEL*)message)->Y, 
                    ((msg::real::BNO055_DATA_ACCEL*)message)->Z);
            break;
        case msg::id::BNO055_DATA_GYRO:
            sprintf(dest, "%d %d %d \n", 
                    ((msg::real::BNO055_DATA_GYRO*)message)->X, 
                    ((msg::real::BNO055_DATA_GYRO*)message)->Y, 
                    ((msg::real::BNO055_DATA_GYRO*)message)->Z);
            break;
        case msg::id::BNO055_DATA_MAG:
            sprintf(dest, "%d %d %d \n", 
                    ((msg::real::BNO055_DATA_MAG*)message)->X, 
                    ((msg::real::BNO055_DATA_MAG*)message)->Y, 
                    ((msg::real::BNO055_DATA_MAG*)message)->Z);
            break;
        }
    }
    
}

