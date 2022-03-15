#include "IO/IOInterface.h"
#include "messageTypes.h"
#include "timer.h"
#include <cstdint>

namespace i2c_operations
{
    struct callback_data
    {
        int fileDescriptor;
        int slave_address;
        IO::IOInterface* obj;
    };

    /* Function Definitions */
    void ALTIMETER_READ_CONFIG(int fileDescriptor, int slave_address, IO::IOInterface* obj);
    void ALTIMETER_READ_ALTITUDE(int fileDescriptor, int slave_address, IO::IOInterface* obj);

    void HTU20D_READ_HUMIDITY(int fileDescriptor, int slave_address, IO::IOInterface* obj);
    void HTU20D_READ_TEMPERATURE(int fileDescriptor, int slave_address, IO::IOInterface* obj);

    void BNO_READ_ACCEL_DATA(int fileDescriptor, int slave_address, IO::IOInterface* obj);
    void BNO_READ_GYRO_DATA(int fileDescriptor, int slave_address, IO::IOInterface* obj);
    void BNO_READ_MAG_DATA(int fileDescriptor, int slave_address, IO::IOInterface* obj);
    void BNO_SET_OPR_MODE(int fileDescriptor, int slave_address, IO::IOInterface* obj);
    void BNO_SET_AXIS_CONFIG(int fileDescriptor, int slave_address, IO::IOInterface* obj);
    void BNO_SET_UNIT_SELECTION(int fileDescriptor, int slave_address, IO::IOInterface* obj);
    void BNO_SET_ACCEL_CONFIG(int fileDescriptor, int slave_address, IO::IOInterface* obj);
    void BNO_SET_GYRO_CONFIG(int fileDescriptor, int slave_address, IO::IOInterface* obj);
    void BNO_SET_MAG_CONFIG(int fileDescriptor, int slave_address, IO::IOInterface* obj);

    /* Callback Functions */
    void ALTIMETER_READ_ALTITUDE_CALLBACK(sigval data);
}