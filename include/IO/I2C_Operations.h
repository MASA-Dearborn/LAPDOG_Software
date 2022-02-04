#include <cstdint>

void _i2c_read(int fileDescriptor, char* dest, const uint32_t num);
void _i2c_write(int fileDescriptor, uint8_t reg, char* src, const uint32_t num);
void _i2c_set_slave_address(int fileDescriptor, long slave_address);

/* I2C Operations */
void READ_TEST_MESSAGE(int fileDescriptor, int slave_address, char* buffer, int buffer_size);