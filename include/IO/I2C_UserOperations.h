#include "messageTypes.h"
#include <cstdint>

namespace i2c_operations
{
    // Read functions
    void READ_TEST_MESSAGE(int fileDescriptor, int slave_address, msg::GENERIC_MESSAGE* msg);
    void ALTIMETER_READ_TEMP(int fileDescriptor, int slave_address, char* buffer, int buffer_size);
    void ALTIMETER_READ_CONFIG(int fileDescriptor, int slave_address, char* buffer, int buffer_size);
    void ATLIMETER_READ_ALTITUDE(int fileDescriptor, int slave_address, char* buffer, int buffer_size);

    // Delayed callback functions
    void ALTIMETER_READ_TEMP_CALLBACK(int fileDescriptor, int slave_address, char* buffer, int buffer_size);
    void ALTIMETER_READ_CONFIG_CALLBACK(int fileDescriptor, int slave_address, char* buffer, int buffer_size);
    void ALTIMETER_READ_ALTITUDE_CALLBACK(int fileDescriptor, int slave_address, char* buffer, int buffer_size);
}