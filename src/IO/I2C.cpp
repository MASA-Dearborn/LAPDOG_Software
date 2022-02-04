#include "IO/I2C.h"
#include "IO/I2C_Operations.h"

#include <fcntl.h>
#include <unistd.h>

using namespace IO;

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

void I2C_Interface::_registerMessageOperation(long slave_address, void (*read_function)(int, int, char*, int))
{
    if(read_function == nullptr)
        return;

    I2C_Slave_Message temp = {  .slave_address = slave_address,
                                .read_function = read_function  };

    m_slaveMessageOperations.push_back(temp);
}

void I2C_Interface::_thread()
{
    // TODO: Create an approach that lets messages read at different intervals
    while (true) {

        usleep(100000);

        // Read all messages
        for(I2C_Slave_Message operation : m_slaveMessageOperations) {
            operation.read_function(m_fileDescriptor, operation.slave_address, nullptr, 0);
        }

    }
}