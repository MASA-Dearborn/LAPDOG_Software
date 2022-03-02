#include <cstdint>

/* I2C Operations */
namespace i2c_operations
{

    void _i2c_read(int fileDescriptor, char* dest, const uint32_t num);
    void _i2c_write(int fileDescriptor, uint8_t reg, char* src, const uint32_t num);
    void _i2c_set_slave_address(int fileDescriptor, long slave_address);

    // Read functions
    void READ_TEST_MESSAGE(int fileDescriptor, int slave_address, char* buffer, int buffer_size);
    void ALTIMETER_READ_TEMP(int fileDescriptor, int slave_address, char* buffer, int buffer_size);
    void ALTIMETER_READ_CONFIG(int fileDescriptor, int slave_address, char* buffer, int buffer_size);
    void ATLIMETER_READ_ALTITUDE(int fileDescriptor, int slave_address, char* buffer, int buffer_size);

    // Delayed callback functions
    void ALTIMETER_READ_TEMP_CALLBACK(int fileDescriptor, int slave_address, char* buffer, int buffer_size);
    void ALTIMETER_READ_CONFIG_CALLBACK(int fileDescriptor, int slave_address, char* buffer, int buffer_size);
    void ALTIMETER_READ_ALTITUDE_CALLBACK(int fileDescriptor, int slave_address, char* buffer, int buffer_size);
}