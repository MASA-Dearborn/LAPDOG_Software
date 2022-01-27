#include "IO/I2C.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace IO;

static void READ_TEST_MESSAGE(int fileDescriptor, char* buffer, int buffer_size);

I2C_Interface::I2C_Interface()
{

}

I2C_Interface::I2C_Interface(const char* dev_name)
{
    m_deviceName = dev_name;
    _init();
}

I2C_Interface::~I2C_Interface()
{
    m_threadActive = false;
    m_threadObj.join();
    _closeDevice();
}

void I2C_Interface::_init()
{
    /* Registration Functions */
    _registerMessageOperation(0x30, READ_TEST_MESSAGE);

    _openDevice();
    m_threadObj = std::thread(&I2C_Interface::_thread, this);
}

int I2C_Interface::readMessage(uint8_t* dest, const int num)
{
    return RX_BUFFER_PTR.get()->dequeue(dest, num);
}

int I2C_Interface::writeMessage(uint8_t* src, const int num)
{
    return TX_BUFFER_PTR.get()->enqueue(src, num);
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

void I2C_Interface::_registerMessageOperation(long slave_address, void (*read_function)(int, char*, int))
{
    if(read_function == nullptr)
        return;

    I2C_Slave_Message temp = {  .slave_address = slave_address,
                                .read_function = read_function  };

    m_slaveMessageOperations.push_back(temp);
}

void I2C_Interface::_thread()
{

    while (true) {

        usleep(100000);

        for(I2C_Slave_Message operation : m_slaveMessageOperations) {
            operation.read_function(m_fileDescriptor, nullptr, 0);
        }

    }
}

/* I2C Functions */

/**
 * @brief   reads from the I2C device
 * @note    should be called after a I2C write
 * 
 * @param fileDescriptor    an open i2c device file
 * @param dest              the buffer to store the read data in
 * @param num               the amount of bytes to read
 */
static void _i2c_read(int fileDescriptor, char* dest, const uint32_t num)
{
    if (nullptr == dest)
        return;

    read(fileDescriptor, dest, num);
}

/**
 * @brief   writes to the I2C device
 * 
 * @param fileDescriptor    an open i2c device file
 * @param reg               the I2C register to start writing to
 * @param src               the data to write to the registe
 * @param num               the amount of bytes to write
 */
static void _i2c_write(int fileDescriptor, uint8_t reg, char* src, const uint32_t num)
{
    static char data[4096]; 

    if (nullptr == src)
        return;

    data[0] = reg;
    memcpy(&data[1], src, num);

    write(fileDescriptor, data, num + 1);    
}

/**
 * @brief   sets the I2C slave address to work on
 * 
 * @param fileDescriptor    an open i2c device file
 * @param slave_address     the i2c slave address to set
 */
static void _i2c_set_slave_address(int fileDescriptor, long slave_address)
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
        exit(1);
    }
}

/* I2C Message Operation Functions */

static void READ_TEST_MESSAGE(int fileDescriptor, char* buffer, int buffer_size)
{
    _i2c_set_slave_address(fileDescriptor, 0x30);

    char data[] = {64};
    _i2c_write(fileDescriptor, 8, data, 1);

    char ret[13] = {0};
    ret[13] = '\0';
    _i2c_read(fileDescriptor, ret, 12);

    printf("ret = %s\n", ret);
}