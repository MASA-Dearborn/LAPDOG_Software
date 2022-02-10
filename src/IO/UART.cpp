#include "IO/UART.h"
#include <poll.h>
#include <algorithm>

using namespace IO;

UART_Interface::UART_Interface()
{
    _init();
}

UART_Interface::~UART_Interface()
{
    
}

void UART_Interface::_init()
{
    /* Initialize Buffers */
    if (initBuffers() < 0)
		return;

    /* Register Devices */

    /* Register Writeable Messages to Devices */

    /* Setup the Timer */
    io_event_data.ref = this;
    io_event_data.time_count = 0;
    io_timer.setHandler((void (*)(union sigval))&_uart_io_handler);
    io_timer.setHandlerDataPointer(&io_event_data);
    io_timer.setIntervalMilliseconds(UART_IO_INTERVAL_BASE_MS);
    io_timer.setStartDelayMilliseconds(UART_IO_INTERVAL_BASE_MS);
    io_timer.startTimer();
}

void UART_Interface::_registerDevice(const char* name, const char* device_file, speed_t baud)
{
    if (device_count >= MAX_UART_DEVICES)
        return;

    strcpy(devices[device_count].name, name);
    strcpy(devices[device_count].device_file, device_file);

    _openDevice(devices[device_count]);
    _configDevice(devices[device_count], baud);
    device_count++;
}

void UART_Interface::_deviceAddWriteableMessage(const char* device_name, msg::id::MessageType type)
{
    int dev_idx;

    /* Find device with matching name */
    for (dev_idx = 0; dev_idx < device_count; dev_idx++) {
        if (strcmp(device_name, devices[dev_idx].name) == 0)
            break;
    }

    /* Set msg table index to true */
    devices[dev_idx].writeable_messages[type] = true;
}

void UART_Interface::_openDevice(uart_device& device)
{
    device.file_descriptor = open(device.device_file, O_RDWR);
    if(device.file_descriptor < 0)
    {
        printf("Error serial port cannot be opened at: %s\n", device.name);
    }
}

void UART_Interface::_closeDevice(uart_device& device)
{
    close(device.file_descriptor);
}

void UART_Interface::_configDevice(uart_device& device, speed_t baud)
{
    // Following https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/
    // Control Modes
    device.tty.c_cflag &= ~PARENB;         // Disable Parity
    device.tty.c_cflag &= ~CSTOPB;         // Use 1 stop bit
    device.tty.c_cflag &= ~CSIZE;          // Clear all size bits
    device.tty.c_cflag |= CS8;             // Use 8 bit data
    device.tty.c_cflag &= ~CRTSCTS;        // Disable RTS/CTS 
    device.tty.c_cflag |= CREAD | CLOCAL;  // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    // Local Modes
    device.tty.c_lflag &= ~ICANON;         // Set Canonical
    device.tty.c_lflag &= ~ECHO;           // Disable echo
    device.tty.c_lflag &= ~ECHOE;          // Disable erasure
    device.tty.c_lflag &= ~ECHONL;         // Disable new-line echo
    device.tty.c_lflag &= ~ISIG;           // Disable interpretation of INTR, QUIT and SUSP

    // Input Modes
    device.tty.c_iflag &= ~(IXON | IXOFF | IXANY);                             // Turn off s/w flow ctrl
    device.tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);    // Disable any special handling of received bytes

    // Output Modes
    device.tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    device.tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    // Set Timeouts
    device.tty.c_cc[VTIME] = 0;    // Min timeout
    device.tty.c_cc[VMIN] = 0;     // Min number to read

    // Set Baudrate
    device.baud_rate = baud;
    cfsetispeed(&(device.tty), baud);
    cfsetospeed(&(device.tty), baud);

    int errno;
    if (tcsetattr(device.file_descriptor, TCSANOW, &device.tty) != 0) 
    {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }
}

int _uart_read(uart_device& device, uint8_t* dest, const int num)
{
    if(dest == nullptr)
        return -1;

    return read(device.file_descriptor, dest, num);
}

int _uart_write(uart_device& device, uint8_t* src, const int num)
{
    if(src == nullptr)
        return -1;

    int retVal = write(device.file_descriptor, src, num);
    if(retVal < 0)
        return -1;

    return retVal;
}

void IO::_uart_io_handler(union sigval data)
{
    static uint8_t buffer[BUFFER_SIZE];
    uart_timer_data* args = (uart_timer_data*)data.sival_ptr;
    UART_Interface* obj = (UART_Interface*)args->ref;
    int ret = 0;

    /* Write available messages to specific devices */
    if (obj->TX_BUFFER_PTR.get()->getDataSize() > 0)
    {
        /* Read message into the buffer */
        msg::GENERIC_MESSAGE* temp = (msg::GENERIC_MESSAGE*)obj->TX_BUFFER_PTR.get()->peek();
        obj->TX_BUFFER_PTR.get()->dequeue(buffer, temp->size);
        temp = (msg::GENERIC_MESSAGE*)buffer;

        /* Check to see which devices can write the message */
        std::for_each (obj->devices.begin(), obj->devices.begin() + obj->device_count, [&](uart_device& device)
        {
            if (device.file_descriptor == -1)
                return;

            /* Device can write this message */
            if (true == device.writeable_messages[temp->id])
            {
                _uart_write(device, buffer, temp->size);
            }
        });
    }

    /* Read message from devices */
    std::for_each (obj->devices.begin(), obj->devices.begin() + obj->device_count, [&](uart_device& device)
    {
        if (device.file_descriptor == -1)
            return;

        ret = _uart_read(device, buffer, BUFFER_SIZE);
        if (ret > 0)
            obj->RX_BUFFER_PTR.get()->enqueue(buffer, ret);
    });

    args->time_count += UART_IO_INTERVAL_BASE_MS;
}
