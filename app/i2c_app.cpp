#include "datalogger/dataLogger.h"
#include "IO/MessageHandler.h"
#include "broker/broker.h"
#include "IO/I2C.h"
#include "IO/I2C_UserOperations.h"
#include "IO/I2C_Devices.h"

#include <iostream>
#include <unistd.h>
#include <cstdio>

using namespace IO;

/* Objects */
//DataLogger g_DataLogger;
MessageHandler g_MessageHandler;
I2C_Interface g_I2C;

/* Publishers & Subscribers */
pubsub::GenericPublisher*  g_Pubs[msg::id::META_NUM_MESSAGES] = {0};
pubsub::GenericSubscriber* g_Subs[msg::id::META_NUM_MESSAGES] = {0};

/* Misc variables */
char string_buf[1024];

/* Screen Buffer*/
const int rows = 8;
const int cols = 128;
char screen_buf[rows*cols] = {' '};

/* ART */ 
// Generated using https://patorjk.com/software/taag/#p=display&h=2&f=Slant&t=MASA
// Slant font
const char* MASA_LOGO[5] = {    
    "    __  ______   _____ ___ ",
    "   /  |/  /   | / ___//   |",
    "  / /|_/ / /| | \\__ \\/ /| |",
    " / /  / / ___ |___/ / ___ |",
    "/_/  /_/_/  |_/____/_/  |_|",
}; 

/* Function Prototypes */
void setupDataLogger();
void setupPublishersAndSubscribers();
void publishDefaultMessages();
void setupI2C();
void setupMessageHandler();

/* Terminal Output Function Prototypes */
char* curPos(int row, int col);
void setupScreenBuffer();
void drawScreenBuffer();

uint32_t getsp( void )
{
    volatile uint32_t address = 0;
    asm volatile ("mov %0, sp\n\t"
     : "=r" ( address)
     );
    return address;
}

int main()
{
    using namespace msg::id;

    setupScreenBuffer();
    setupPublishersAndSubscribers();
    setupI2C();
    setupMessageHandler();
    //setupDataLogger();
    publishDefaultMessages();

    char buffer[256];
    uint32_t count = 0;
    while(true)
    {
        strcpy(curPos(0,0), MASA_LOGO[0]);
        strcpy(curPos(1,0), MASA_LOGO[1]);
        strcpy(curPos(2,0), MASA_LOGO[2]);
        strcpy(curPos(3,0), MASA_LOGO[3]);
        strcpy(curPos(4,0), MASA_LOGO[4]);

        sprintf(curPos(0, 32), "COUNT: %d", count);
        sprintf(curPos(0, 64), "SP: %x", getsp());
        count++;

        if (g_Subs[ALTIMETER_DATA]->isDataAvailable())
        {
            msg::conv::stringifyRealMessage(buffer, (msg::GENERIC_MESSAGE*)g_Subs[ALTIMETER_DATA]->getGenericPointer());
            sprintf(curPos(1,32),"ALT: %s", buffer);
        }

        if (g_Subs[HUMIDITY_DATA]->isDataAvailable())
        {
            msg::conv::stringifyRealMessage(buffer, (msg::GENERIC_MESSAGE*)g_Subs[HUMIDITY_DATA]->getGenericPointer());
            sprintf(curPos(1,64),"HUM: %s", buffer);
        }

        if (g_Subs[BNO055_DATA_ACCEL]->isDataAvailable())
        {
            msg::conv::stringifyRealMessage(buffer, (msg::GENERIC_MESSAGE*)g_Subs[BNO055_DATA_ACCEL]->getGenericPointer());
            sprintf(curPos(2,32),"ACL: %s", buffer);
        }

        if (g_Subs[BNO055_DATA_GYRO]->isDataAvailable())
        {
            msg::conv::stringifyRealMessage(buffer, (msg::GENERIC_MESSAGE*)g_Subs[BNO055_DATA_GYRO]->getGenericPointer());
            sprintf(curPos(2,64),"GYR: %s", buffer);
        }

        if (g_Subs[ALTIMETER_COEFFS]->isDataAvailable())
        {
            msg::conv::stringifyRealMessage(buffer, (msg::GENERIC_MESSAGE*)g_Subs[ALTIMETER_COEFFS]->getGenericPointer());
            sprintf(curPos(3,32),"COE: %s", buffer);
        }

        drawScreenBuffer();
        usleep(100000);
    }
}

void setupDataLogger()
{
    using namespace msg::id;
    // g_DataLogger.addLoggableMessage(TEST_MESSAGE_READ, 5000);
    // g_DataLogger.addLoggableMessage(TEST_MESSAGE_READ, 5000);
    // g_DataLogger.addLoggableMessage(TEST_MESSAGE_WRITE, 5000);
    // g_DataLogger.addLoggableMessage(BNO055_PAGE, 5000);
    // g_DataLogger.addLoggableMessage(ALTIMETER_COEFFS, 5000);
    // g_DataLogger.addLoggableMessage(ALTIMETER_DATA, 5000);
    // g_DataLogger.addLoggableMessage(HUMIDITY_DATA, 5000);
    // g_DataLogger.addLoggableMessage(BNO055_ACCEL_CONFIG, 5000);
    // g_DataLogger.addLoggableMessage(BNO055_GYRO_CONFIG, 5000);
    // g_DataLogger.addLoggableMessage(BNO055_MAG_CONFIG, 5000);
    // g_DataLogger.addLoggableMessage(BNO055_OPR_MODE, 5000);
    // g_DataLogger.addLoggableMessage(BNO055_AXIS_CONFIG, 5000);
    // g_DataLogger.addLoggableMessage(BNO055_UNIT_SELECTION, 5000);
    // g_DataLogger.addLoggableMessage(BNO055_CAL_ACCEL, 5000);
    // g_DataLogger.addLoggableMessage(BNO055_CAL_MAG, 5000);
    // g_DataLogger.addLoggableMessage(BNO055_CAL_GYRO, 5000);
    // g_DataLogger.addLoggableMessage(BNO055_DATA_ACCEL, 5000);
    // g_DataLogger.addLoggableMessage(BNO055_DATA_GYRO, 5000);
    // g_DataLogger.addLoggableMessage(BNO055_DATA_MAG, 5000);
}

void setupPublishersAndSubscribers()
{
    using namespace msg::id;
    using namespace pubsub;

    /* Setup Publishers */
    g_Pubs[BNO055_OPR_MODE]         = generatePublisher(BNO055_OPR_MODE);
    g_Pubs[BNO055_AXIS_CONFIG]      = generatePublisher(BNO055_AXIS_CONFIG);
    g_Pubs[BNO055_UNIT_SELECTION]   = generatePublisher(BNO055_UNIT_SELECTION);
    g_Pubs[BNO055_ACCEL_CONFIG]     = generatePublisher(BNO055_ACCEL_CONFIG);
    g_Pubs[BNO055_GYRO_CONFIG]      = generatePublisher(BNO055_GYRO_CONFIG);
    g_Pubs[BNO055_MAG_CONFIG]       = generatePublisher(BNO055_MAG_CONFIG);

    /* Setup Subscribers */
    g_Subs[BNO055_DATA_ACCEL]   = generateSubscriber(BNO055_DATA_ACCEL);
    g_Subs[BNO055_DATA_GYRO]    = generateSubscriber(BNO055_DATA_GYRO);
    g_Subs[ALTIMETER_DATA]      = generateSubscriber(ALTIMETER_DATA);
    g_Subs[HUMIDITY_DATA]       = generateSubscriber(HUMIDITY_DATA);
    g_Subs[ALTIMETER_COEFFS]    = generateSubscriber(ALTIMETER_COEFFS);
}

void publishDefaultMessages()
{
    using namespace msg::id;

    msg::real::BNO055_AXIS_CONFIG m2;
    usleep(1000);

    msg::real::BNO055_UNIT_SELECTION m3;
    m3.ACCELERATION = 0;
    m3.ANGULAR_RATE = 0;
    m3.EULER_ANGLES = 0;
    m3.TEMPERATURE = 0;
    g_Pubs[BNO055_OPR_MODE]->publish(&m3);
    usleep(10000);

    msg::real::BNO055_ACCEL_CONFIG m4;
    m4.G_RANGE = 3;
    m4.OPERATION_MODE = 0;
    m4.SAMPLE_RATE = 4;
    g_Pubs[BNO055_ACCEL_CONFIG]->publish(&m4);
    usleep(10000);

    msg::real::BNO055_GYRO_CONFIG m5;
    m5.OPERATION_MODE = 0;
    m5.SAMPLE_RATE = 3;
    m5.RANGE = 2;
    g_Pubs[BNO055_GYRO_CONFIG]->publish(&m5);
    usleep(10000);

    msg::real::BNO055_MAG_CONFIG m6;
    m6.OPERATION_MODE = 1;
    m6.SAMPLE_RATE = 6;
    g_Pubs[BNO055_MAG_CONFIG]->publish(&m6);
    usleep(10000);

    // Must be written last
    msg::real::BNO055_OPR_MODE m1;
    m1.MODE = (char)BNO055_OPERATION_MODE::AMG;
    g_Pubs[BNO055_OPR_MODE]->publish(&m1);
    usleep(10000);

}

void setupI2C()
{
    /* Register Devices*/
    g_I2C.registerDevice("DEV1", "/dev/i2c-0", 0x76);
    g_I2C.registerDevice("DEV2", "/dev/i2c-0", 0x40);
    g_I2C.registerDevice("DEV3", "/dev/i2c-0", 0x28);

    /* Register Functions */
    g_I2C.registerInitFunction("DEV1", i2c_operations::ALTIMETER_READ_CONFIG);
    // g_I2C.registerInitFunction("DEV2", i2c_operations::HTU20D_SET_USER_REG);

    // Altimeter Funcs
    g_I2C.registerOperation("DEV1", I2C_READ, msg::id::ALTIMETER_DATA, 50, i2c_operations::ALTIMETER_READ_ALTITUDE);

    // Humidity Funcs
    // g_I2C.registerOperation("DEV2", I2C_READ, msg::id::HUMIDITY_DATA, 50, i2c_operations::HTU20D_READ_HUMIDITY);
    // g_I2C.registerOperation("DEV2", I2C_READ, msg::id::HUMIDITY_DATA, 50, i2c_operations::HTU20D_READ_TEMPERATURE);

    // IMU Funcs
    g_I2C.registerOperation("DEV3", I2C_READ, msg::id::BNO055_DATA_ACCEL, 50, i2c_operations::BNO_READ_ACCEL_DATA);
    g_I2C.registerOperation("DEV3", I2C_READ, msg::id::BNO055_DATA_GYRO, 50, i2c_operations::BNO_READ_GYRO_DATA);
    g_I2C.registerOperation("DEV3", I2C_READ, msg::id::BNO055_DATA_MAG, 50, i2c_operations::BNO_READ_MAG_DATA);
    g_I2C.registerOperation("DEV3", I2C_WRITE, msg::id::BNO055_OPR_MODE, 50, i2c_operations::BNO_SET_OPR_MODE);
    g_I2C.registerOperation("DEV3", I2C_WRITE, msg::id::BNO055_AXIS_CONFIG, 50, i2c_operations::BNO_SET_AXIS_CONFIG);
    g_I2C.registerOperation("DEV3", I2C_WRITE, msg::id::BNO055_UNIT_SELECTION, 50, i2c_operations::BNO_SET_UNIT_SELECTION);
    g_I2C.registerOperation("DEV3", I2C_WRITE, msg::id::BNO055_ACCEL_CONFIG, 50, i2c_operations::BNO_SET_ACCEL_CONFIG);
    g_I2C.registerOperation("DEV3", I2C_WRITE, msg::id::BNO055_GYRO_CONFIG, 50, i2c_operations::BNO_SET_GYRO_CONFIG);
    g_I2C.registerOperation("DEV3", I2C_WRITE, msg::id::BNO055_MAG_CONFIG, 50, i2c_operations::BNO_SET_MAG_CONFIG);
}

void setupMessageHandler()
{
    defaultMessageHandlerSetup(g_MessageHandler);
    
    /* Attach Interfaces */
    g_MessageHandler.attachIOInterface(&g_I2C);
}

char* curPos(int row, int col)
{
    return &screen_buf[row*cols + col];
}

void setupScreenBuffer()
{
    system("clear");
    memset(screen_buf, ' ', rows*cols);
    for (int i = 0; i < rows; i++)
    {
        *curPos(i, cols-1) = '\n';
    }
    *curPos(rows - 1, cols-1) = '\0';
}

void drawScreenBuffer()
{
    // Remove newlines and string ends
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols - 1; c++)
        {
            char* val = curPos(r, c);
            if ((*val) == '\n' || (*val) == '\0')
                (*val) = ' ';
        }
    }

    // Output buffer
    std::cout << "\033[0;0H" << screen_buf << std::endl;

    // Reset buffer
    memset(screen_buf, ' ', rows*cols);
    for (int i = 0; i < rows; i++)
    {
        *curPos(i, cols-1) = '\n';
    }
    *curPos(rows - 1, cols-1) = '\0';

}