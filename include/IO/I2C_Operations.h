#include "messageTypes.h"
#include <cstdint>

/* I2C Operations */
namespace i2c_operations
{
    void _i2c_read(int fileDescriptor, char* dest, const uint32_t num);
    void _i2c_write(int fileDescriptor, uint8_t reg, char* src, const uint32_t num);
    char _i2c_read_one(int fileDescriptor);
    void _i2c_write_one(int fileDescriptor, uint8_t data)
    void _i2c_set_slave_address(int fileDescriptor, long slave_address);
}