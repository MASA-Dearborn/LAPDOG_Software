#include "IO/I2C_Operations.h"
#include "IO/I2C_UserOperations.h"
#include "timer.h"

void i2c_operations::READ_TEST_MESSAGE(int fileDescriptor, int slave_address, msg::GENERIC_MESSAGE* msg)
{
    _i2c_set_slave_address(fileDescriptor, slave_address);

    char data[64] = {64};
    _i2c_write(fileDescriptor, 8, data, 4);

    char ret[13] = {0};
    ret[13] = '\0';
    _i2c_read(fileDescriptor, ret, 12);
    printf("E: %d\n", slave_address);
}

void i2c_operations::ALTIMETER_READ_TEMP(int fileDescriptor, int slave_address, char* buffer, int buffer_size)
{

}

void i2c_operations::ALTIMETER_READ_CONFIG(int fileDescriptor, int slave_address, char* buffer, int buffer_size)
{

}

void i2c_operations::ALTIMETER_READ_CONFIG_CALLBACK(int fileDescriptor, int slave_address, char* buffer, int buffer_size)
{

}

void i2c_operations::ALTIMETER_READ_ALTITUDE_CALLBACK(int fileDescriptor, int slave_address, char* buffer, int buffer_size)
{

}

void i2c_operations::ALTIMETER_READ_TEMP_CALLBACK(int fileDescriptor, int slave_address, char* buffer, int buffer_size)
{
    
}
