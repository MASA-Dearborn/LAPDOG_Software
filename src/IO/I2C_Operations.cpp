#include "IO/I2C_Operations.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <cstring>

using namespace i2c_operations;

/**
 * @brief   reads from the I2C device
 * @note    should be called after a I2C write
 * 
 * @param fileDescriptor    an open i2c device file
 * @param dest              the buffer to store the read data in
 * @param num               the amount of bytes to read
 */
void i2c_operations::_i2c_read(int fileDescriptor, char* dest, const uint32_t num)
{
    if (nullptr == dest)
        return;

    read(fileDescriptor, dest, num);
}

/**
 * @brief   Read one byte from I2C device
 * 
 * @param fileDescriptor    an open i2c device file
 * @return char             the byte read from the device
 */
char i2c_operations::_i2c_read_one(int fileDescriptor)
{
    char temp;
    read(fileDescriptor, &temp, 1);
    return temp
}

/**
 * @brief   writes to the I2C device
 * 
 * @param fileDescriptor    an open i2c device file
 * @param reg               the I2C register to start writing to
 * @param src               the data to write to the registe
 * @param num               the amount of bytes to write
 */
void i2c_operations::_i2c_write(int fileDescriptor, uint8_t reg, char* src, const uint32_t num)
{
    static char data[4096]; 

    if (nullptr == src && 0 != num)
        return;

    data[0] = reg;

    if (num > 0)
        memcpy(&data[1], src, num);

    write(fileDescriptor, data, num + 1);    
}

/**
 * @brief   writes one byte to the I2C device
 * 
 * @param fileDescriptor    an open i2c device file
 * @param data              the data to write
 */
void i2c_operations::_i2c_write_one(int fileDescriptor, uint8_t data)
{
    write(fileDescriptor, data, 1); 
}

/**
 * @brief   sets the I2C slave address to work on
 * 
 * @param fileDescriptor    an open i2c device file
 * @param slave_address     the i2c slave address to set
 */
void i2c_operations::_i2c_set_slave_address(int fileDescriptor, long slave_address)
{
    static long current_slave_address = 0;

    // check if address already set
    if (slave_address == current_slave_address) {
        return;
    } else {
        current_slave_address = slave_address;
    }

    // set slave address
    if (ioctl(fileDescriptor, I2C_SLAVE, slave_address) < 0) {
        return;
    }
}