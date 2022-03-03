#include "IO/I2C_Operations.h"
#include "IO/I2C_UserOperations.h"

void i2c_operations::READ_TEST_MESSAGE(int fileDescriptor, int slave_address, msg::GENERIC_MESSAGE* msg)
{
    _i2c_set_slave_address(fileDescriptor, slave_address);

    char data[64] = {64};
    _i2c_write(fileDescriptor, 8, data, 4);

    char ret[13] = {0};
    ret[13] = '\0';
    _i2c_read(fileDescriptor, ret, 12);

    callback_data temp = {.fileDescriptor = fileDescriptor, .slave_address = slave_address, .msg = msg};
    Timer callback_timer = Timer(&ALTIMETER_READ_TEMP_CALLBACK, &temp, 0, 40);
}

void i2c_operations::ALTIMETER_READ_TEMP(int fileDescriptor, int slave_address, msg::GENERIC_MESSAGE* msg)
{

}

void i2c_operations::ALTIMETER_READ_CONFIG(int fileDescriptor, int slave_address, msg::GENERIC_MESSAGE* msg)
{

}

void i2c_operations::ALTIMETER_READ_CONFIG_CALLBACK(sigval data)
{

}

void i2c_operations::ALTIMETER_READ_ALTITUDE_CALLBACK(sigval data)
{

}

void i2c_operations::ALTIMETER_READ_TEMP_CALLBACK(sigval data)
{
    char ret[16] = {0};
    callback_data* c = (callback_data*)data.sival_ptr;
    _i2c_set_slave_address(c->fileDescriptor, c->slave_address);
    _i2c_read(c->fileDescriptor, ret, 4);
}
