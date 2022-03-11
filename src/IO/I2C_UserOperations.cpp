#include "IO/I2C_Operations.h"
#include "IO/I2C_UserOperations.h"
#include "IO/I2C_Devices.h"

void _setup_callback(unsigned long delay_ms, void (*func)(sigval), int fileDescriptor, int slave_address, msg::GENERIC_MESSAGE* msg)
{
    i2c_operations::callback_data temp = {.fileDescriptor = fileDescriptor, .slave_address = slave_address, .msg = msg};
    Timer callback_timer = Timer(func, &temp, 0, delay_ms);
}

void i2c_operations::ALTIMETER_READ_ALTITUDE(int fileDescriptor, int slave_address, msg::GENERIC_MESSAGE* msg)
{
    _setup_callback(20, &ALTIMETER_READ_ALTITUDE_CALLBACK, fileDescriptor, slave_address, msg);
}

void i2c_operations::ALTIMETER_READ_CONFIG(int fileDescriptor, int slave_address, msg::GENERIC_MESSAGE* msg)
{
    msg::real::ALTIMETER_COEFFS* m = (msg::real::ALTIMETER_COEFFS*)msg; 
    _i2c_set_slave_address(fileDescriptor, slave_address);

    _i2c_write(fileDescriptor, MS5083_ALTIMETER_COMMANDS::PROM_READ_COEFF_1, NULL, 0);

}

void i2c_operations::ALTIMETER_READ_ALTITUDE_CALLBACK(sigval data)
{

}
