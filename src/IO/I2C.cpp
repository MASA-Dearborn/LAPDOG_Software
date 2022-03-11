#include "IO/I2C.h"
#include "IO/I2C_UserOperations.h"

#include <algorithm>
#include <fcntl.h>
#include <unistd.h>

using namespace IO;

I2C_Interface::I2C_Interface()
{
    io_event_data.ref = this;
    io_event_data.time_count = 0;
    _init();
}

I2C_Interface::~I2C_Interface()
{

}

void I2C_Interface::_init()
{
    /* Initialize Buffers */
    if (initBuffers() < 0)
		return;

    /* Reigster Devices */
    _registerDevice("device", "/dev/i2c-0", 0x50);

    /* Registration Functions */
    _registerOperation("device", I2C_READ, msg::id::ALTIMETER_COEFFS, 1000, i2c_operations::ALTIMETER_READ_CONFIG);

    /* Start Timer */
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

void I2C_Interface::_openDevice(i2c_device& device)
{
    device.file_descriptor = open(device.device_file, O_RDWR);
    if (device.file_descriptor < 0)
        printf("Error I2C device '%s' does not exist\n", device.device_file);
}

void I2C_Interface::_closeDevice(i2c_device& device)
{
    close(device.file_descriptor);
}

void I2C_Interface::_registerDevice(const char* name, const char* device_file, int slave_address)
{
    if (device_count >= MAX_I2C_DEVICES)
        return;

    strcpy(devices[device_count].name, name);
    strcpy(devices[device_count].device_file, device_file);
    devices[device_count].slave_address = slave_address;

    _openDevice(devices[device_count]);
    device_count++;
}

void I2C_Interface::_registerOperation(const char* device_name, I2C_OperationType type, msg::id::MessageType msg_id, int interval_ms, void (*func)(int, int, msg::GENERIC_MESSAGE*))
{
    // Find device with matching name
    int dev_idx;
    for (dev_idx = 0; dev_idx < device_count; dev_idx++) {
        if (strcmp(device_name, devices[dev_idx].name) == 0)
            break;
    }

    // Add operation to device
    I2C_Slave_Message temp;
    temp.interval_ms = interval_ms;
    temp.function = func;
    temp.msg_type = msg_id;

    i2c_device& dev = (devices[dev_idx]);

    switch (type) {
        case I2C_WRITE:
            if (dev.num_write_operations > MAX_I2C_OPERATIONS)
                break;

            dev.write_operations.at(dev.num_write_operations) = temp;
            dev.num_write_operations++;
            break;

        case I2C_READ:
            if (dev.num_read_operations > MAX_I2C_OPERATIONS)
                break;

            dev.read_operations.at(dev.num_read_operations) = temp;
            dev.num_read_operations++;
            break;
    }
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

    /* Write message to devices */
    while (obj->TX_BUFFER_PTR.get()->getDataSize() > 0)
    {
        msg::GENERIC_MESSAGE* temp = (msg::GENERIC_MESSAGE*)obj->TX_BUFFER_PTR.get()->peek();
        obj->TX_BUFFER_PTR.get()->dequeue(data_buffer, temp->size);
        temp = (msg::GENERIC_MESSAGE*)data_buffer;

        std::for_each (obj->devices.begin(), obj->devices.begin() + obj->device_count, [&](i2c_device& device)
        {
            if (device.file_descriptor == -1)
                return;

            std::for_each (device.write_operations.begin(), device.write_operations.begin() + device.num_write_operations, [&](I2C_Slave_Message& op) {
                if (op.msg_type == temp->id)
                    op.function(device.file_descriptor, device.slave_address, temp);
            });
        });
    }

    /* Read message from devices */
    std::for_each (obj->devices.begin(), obj->devices.begin() + obj->device_count, [&](i2c_device& device)
    {
        if (device.file_descriptor == -1)
            return;

        std::for_each (device.read_operations.begin(), device.read_operations.begin() + device.num_read_operations, [&](I2C_Slave_Message& op) {
            if (_timeIntervalPassed(op.last_trigger, args->time_count, op.interval_ms))
                op.function(device.file_descriptor, device.slave_address, (msg::GENERIC_MESSAGE*)data_buffer);

            obj->RX_BUFFER_PTR.get()->enqueue(data_buffer, ((msg::GENERIC_MESSAGE*)data_buffer)->size);
        });
    });

    // Increment time
    args->time_count += I2C_IO_INTERVAL_BASE_MS;

}