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
    char buffer[16];
    msg::raw::ALTIMETER_COEFFS* m = (msg::raw::ALTIMETER_COEFFS*)msg; 
    *m = msg::raw::ALTIMETER_COEFFS();
    _i2c_set_slave_address(fileDescriptor, slave_address);

    // Read Coefficients
    _i2c_write_one(fileDescriptor, (uint8_t)MS5083_ALTIMETER_COMMANDS::PROM_READ_COEFF_1);
    _i2c_read(fileDescriptor, buffer, 2);
    m->coeff_1 = *(uint16_t*)buffer;

    _i2c_write_one(fileDescriptor, (uint8_t)MS5083_ALTIMETER_COMMANDS::PROM_READ_COEFF_2);
    _i2c_read(fileDescriptor, buffer, 2);
    m->coeff_2 = *(uint16_t*)buffer;

    _i2c_write_one(fileDescriptor, (uint8_t)MS5083_ALTIMETER_COMMANDS::PROM_READ_COEFF_3);
    _i2c_read(fileDescriptor, buffer, 2);
    m->coeff_3 = *(uint16_t*)buffer;

    _i2c_write_one(fileDescriptor, (uint8_t)MS5083_ALTIMETER_COMMANDS::PROM_READ_COEFF_4);
    _i2c_read(fileDescriptor, buffer, 2);
    m->coeff_4 = *(uint16_t*)buffer;

    _i2c_write_one(fileDescriptor, (uint8_t)MS5083_ALTIMETER_COMMANDS::PROM_READ_COEFF_5);
    _i2c_read(fileDescriptor, buffer, 2);
    m->coeff_5 = *(uint16_t*)buffer;

    _i2c_write_one(fileDescriptor, (uint8_t)MS5083_ALTIMETER_COMMANDS::PROM_READ_COEFF_6);
    _i2c_read(fileDescriptor, buffer, 2);
    m->coeff_6 = *(uint16_t*)buffer;
}

void i2c_operations::ALTIMETER_READ_ALTITUDE_CALLBACK(sigval data)
{

}
