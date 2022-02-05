#include "IO/SPI.h"
#include "IO/SPI_Operations.h"

#include <algorithm>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

using namespace IO;

SPI_Interface::SPI_Interface()
{
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
    // TODO: Define all default SPI devices here
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
void SPI_Interface::_registerDevice(const char* name, const char* device_file)
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
void SPI_Interface::_registerOperation(const char* device_name, SPI_OperationType type, int interval_ms, int (*func)(int, msg::GENERIC_MESSAGE*))
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

void SPI_Interface::_thread()
{

}
