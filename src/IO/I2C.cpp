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
    _closeDevice();
}

void I2C_Interface::_init()
{
    /* Registration Functions */
    _registerMessageOperation(0x30, 100, READ_TEST_MESSAGE);
    _openDevice();
    
    /* Start Timer */
    io_event_data.time_count = 0;
    io_event_data.ref = this;
    io_timer.setHandler((void (*)(union sigval))&_i2c_io_handler);
    io_timer.setHandlerDataPointer(&io_event_data);
    io_timer.setIntervalMilliseconds(I2C_IO_INTERVAL_BASE_MS);
    io_timer.setStartDelayMilliseconds(I2C_IO_INTERVAL_BASE_MS);
    io_timer.startTimer();

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

void I2C_Interface::_registerMessageOperation(long slave_address, int interval_ms, void (*read_function)(int, int, char*, int))
{
    if(read_function == nullptr)
        return;

    I2C_Slave_Message temp;
    temp.read_function = read_function;
    temp.slave_address = slave_address;
    temp.interval_ms = interval_ms;

    m_slaveMessageOperations.push_back(temp);
}

static bool _timeIntervalPassed(uint64_t& last_trigger, uint64_t& current_time, uint64_t& interval)
{
    if ((current_time - last_trigger) > interval)
    {
        last_trigger = current_time;
        return true;
    } else {
        return false;
    }
}

void IO::_i2c_io_handler(union sigval data)
{
    /* Get the needed references from data */
    i2c_timer_data* args = (i2c_timer_data*)data.sival_ptr;
    I2C_Interface* obj = (I2C_Interface*)args->ref;
    static uint8_t data_buffer[1024];

    // Read all messages
    for(I2C_Slave_Message& operation : obj->m_slaveMessageOperations) {
        if (_timeIntervalPassed(operation.last_trigger, obj->io_event_data.time_count, operation.interval_ms))
            printf("Test!\n");
            //operation.read_function(obj->m_fileDescriptor, operation.slave_address, nullptr, 0);
    }

}