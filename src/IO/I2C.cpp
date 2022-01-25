#include "IO/I2C.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace IO;

I2C_Interface::I2C_Interface()
{

}

I2C_Interface::I2C_Interface(const char* dev_name)
{

}

I2C_Interface::~I2C_Interface()
{

}

int I2C_Interface::readMessage(uint8_t* dest, const int num)
{

}

int I2C_Interface::writeMessage(uint8_t* src, const int num)
{

}

void I2C_Interface::_init()
{

}

void I2C_Interface::_openDevice()
{
    m_fileDescriptor = open(m_deviceName, O_RDWR);
    if(m_fileDescriptor < 0)
    {
        printf("Error serial port cannot be opened at: %s\n", m_deviceName);
    }
}

void I2C_Interface::_closeDevice()
{
    close(m_fileDescriptor);
}

void I2C_Interface::_setSlaveAddress(long address)
{

}

void I2C_Interface::_registerMessageOperation(long slave_address, void (*read_function)(int, char*, int))
{
    if(read_function == nullptr)
        return;

    I2C_Slave_Message temp = {  .slave_address = slave_address,
                                .read_function = read_function  };

    m_slaveMessageOperations.push_back(temp);
}

/* I2C Functions */

static void _i2c_read(int fileDescriptor, char* dest, const int num)
{
  
}

static void _i2c_write(int fileDescriptor, int reg, char* src, const int num)
{
  
}

static void _i2c_set_slave_address(int fileDescriptor, long slave_address)
{
    if (ioctl(fileDescriptor, I2C_SLAVE, slave_address) < 0) {
        exit(1);
    }
}


/* I2C Message Operation Functions */

static void READ_TEST_MESSAGE(int fileDescriptor, char* buffer, int buffer_size)
{

}