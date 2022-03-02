#include "IO/I2C_Operations.h"

using namespace i2c_operations;

void READ_TEST_MESSAGE(int fileDescriptor, int slave_address, char* buffer, int buffer_size)
{
    _i2c_set_slave_address(fileDescriptor, slave_address);

    char data[] = {64};
    _i2c_write(fileDescriptor, 8, data, 1);

    char ret[13] = {0};
    ret[13] = '\0';
    _i2c_read(fileDescriptor, ret, 12);
}

void ALTIMETER_READ_TEMP(int fileDescriptor, int slave_address, char* buffer, int buffer_size)
{

}
void ALTIMETER_READ_CONFIG(int fileDescriptor, int slave_address, char* buffer, int buffer_size)
{

}

void ATLIMETER_READ_ALTITUDE_CALLBACK(int fileDescriptor, int slave_address, char* buffer, int buffer_size)
{

}

void ALTIMETER_READ_ALTITUDE_CALLBACK(int fileDescriptor, int slave_address, char* buffer, int buffer_size)
{

}

void ALTIMETER_READ_TEMP_CALLBACK(int fileDescriptor, int slave_address, char* buffer, int buffer_size)
{
    
}