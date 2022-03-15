#include "IO/SPI.h"
#include "IO/SPI_Operations.h"

#include <algorithm>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

using namespace IO;

static bool _timeIntervalPassed(uint64_t& last_trigger, uint64_t& current_time, uint64_t& interval);

SPI_Interface::SPI_Interface()
{
    this->type = TYPE_SPI;
    io_event_data.ref = this;
    io_event_data.time_count = 0;
    _init();
}

SPI_Interface::~SPI_Interface()
{
    std::for_each(devices.begin(), devices.end(), [this](spi_device& dev){
        _closeDevice(dev);
    });
}

int SPI_Interface::readMessage(uint8_t* dest, const int num)
{
    return RX_BUFFER_PTR.get()->dequeue(dest, num);
}

int SPI_Interface::writeMessage(uint8_t* src, const int num)
{
    return TX_BUFFER_PTR.get()->enqueue(src, num);
}

/**
 * @brief   Register devices and operations
 * 
 */
void SPI_Interface::_init()
{
    /* Initialize Buffers */
    if (initBuffers() < 0)
		return;

    /* Setup the Timer */
    io_timer.setHandler((void (*)(union sigval))&_spi_io_handler);
    io_timer.setHandlerDataPointer(&io_event_data);
    io_timer.setIntervalMilliseconds(SPI_IO_INTERVAL_BASE_MS);
    io_timer.setStartDelayMilliseconds(SPI_IO_INTERVAL_BASE_MS);
    io_timer.startTimer();
}

/**
 * @brief   Open the device file associated with device
 * 
 * @param device    the spi_device reference to open
 */
void SPI_Interface::_openDevice(spi_device& device)
{
    device.file_descriptor = open(device.device_file, O_RDWR);
    if (device.file_descriptor < 0)
        printf("Error SPI device '%s' does not exist\n", device.device_file);
}

/**
 * @brief   Close a spi_device to prevent further communication
 * 
 * @param device    spi_device reference to shutdown
 */
void SPI_Interface::_closeDevice(spi_device& device)
{
    close(device.file_descriptor);
}

/**
 * @brief   Register a SPI device
 * @note    Should be called in _init()
 * 
 * @param name          The physical device name
 * @param device_file   The devie file associated with the device
 */
void SPI_Interface::registerDevice(const char* name, const char* device_file)
{
    if (device_count >= MAX_SPI_DEVICES)
        return;

    strcpy(devices[device_count].name, name);
    strcpy(devices[device_count].device_file, device_file);

    _openDevice(devices[device_count]);
    device_count++;
}

/**
 * @brief   Register a SPI device operation
 * @note    Should be called in _init()
 * 
 * @param device_name   The devices name to register the function too
 * @param type          A enum of SPI_WRITE or SPI_READ
 * @param interval_ms   The period the function should be called at
 * @param func          Pointer to the operation function
 */
void SPI_Interface::registerOperation(const char* device_name, SPI_OperationType type, msg::id::MessageType msg_id, int interval_ms, int (*func)(int, IOInterface*))
{
    // Find device with matching name
    int dev_idx;
    for (dev_idx = 0; dev_idx < device_count; dev_idx++) {
        if (strcmp(device_name, devices[dev_idx].name) == 0)
            break;
    }

    // Add operation to device
    SPI_Slave_Message temp;
    temp.interval_ms = interval_ms;
    temp.function = func;
    temp.msg_type = msg_id;

    spi_device& dev = (devices[dev_idx]);

    switch (type) {
        case SPI_WRITE:
            if (dev.num_write_operations > MAX_SPI_OPERATIONS)
                break;

            dev.write_operations.at(dev.num_write_operations) = temp;
            dev.num_write_operations++;
            break;

        case SPI_READ:
            if (dev.num_read_operations > MAX_SPI_OPERATIONS)
                break;

            dev.read_operations.at(dev.num_read_operations) = temp;
            dev.num_read_operations++;
            break;
    }
}

void SPI_Interface::registerInitFunction(const char* device_name, void (*func)(int, IOInterface*))
{
    for (int i = 0; i < device_count; i++)
    {
        if (strcmp(devices[i].name, device_name) == 0)
        {
            func(devices[i].file_descriptor, this);
            break;
        }
    }
}

void IO::_spi_io_handler(union sigval data)
{
    /* Get the needed references from data */
    spi_timer_data* args = (spi_timer_data*)data.sival_ptr;
    SPI_Interface* obj = (SPI_Interface*)args->ref;
    static uint8_t data_buffer[1024];

    /* Write message to devices */
    while (obj->TX_BUFFER_PTR.get()->getDataSize() > 0)
    {
        msg::GENERIC_MESSAGE* temp = (msg::GENERIC_MESSAGE*)obj->TX_BUFFER_PTR.get()->peek();

        std::for_each (obj->devices.begin(), obj->devices.begin() + obj->device_count, [&](spi_device& device)
        {
            if (device.file_descriptor == -1)
                return;

            std::for_each (device.write_operations.begin(), device.write_operations.begin() + device.num_write_operations, [&](SPI_Slave_Message& op) {
                if (op.msg_type == temp->id)
                    op.function(device.file_descriptor, obj);
            });
        });
    }

    /* Read message from devices */
    std::for_each (obj->devices.begin(), obj->devices.begin() + obj->device_count, [&](spi_device& device)
    {
        if (device.file_descriptor == -1)
            return;

        std::for_each (device.read_operations.begin(), device.read_operations.begin() + device.num_read_operations, [&](SPI_Slave_Message& op) {
            if (_timeIntervalPassed(op.last_trigger, args->time_count, op.interval_ms))
            {
                op.function(device.file_descriptor, obj);
            }
        });
    });

    // Increment time
    args->time_count += SPI_IO_INTERVAL_BASE_MS;
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