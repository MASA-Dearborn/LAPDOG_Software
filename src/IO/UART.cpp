#include "IO/UART.h"
#include <poll.h>

using namespace IO;

UART_Interface::UART_Interface()
{

}

UART_Interface::UART_Interface(const char* dev_name, speed_t baud_rate)
{
    this->device_name = dev_name;
    this->baud_rate = baud_rate;

    _openDevice();
    _configDevice();

    this->thread_active = true;
    std::thread(&UART_Interface::_thread, this);
}

UART_Interface::~UART_Interface()
{
    _closeDevice();
}

int UART_Interface::_read(uint8_t* dest, const int num)
{
    if(dest == nullptr)
        return -1;

    return read(serial_port, dest, num);
}

int UART_Interface::_write(uint8_t* src, const int num)
{
    if(src == nullptr)
        return -1;

    int retVal = write(serial_port, src, num);
    if(retVal < 0)
        return -1;

    return retVal;
}

void UART_Interface::_openDevice()
{
    serial_port = open(device_name, O_RDWR);
    if(serial_port < 0)
    {
        printf("Error serial port cannot be opened at: %s\n", device_name);
    }
}

void UART_Interface::_closeDevice()
{
    close(serial_port);
}

void UART_Interface::_configDevice()
{
    // Following https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/
    // Control Modes
    tty.c_cflag &= ~PARENB;         // Disable Parity
    tty.c_cflag &= ~CSTOPB;         // Use 1 stop bit
    tty.c_cflag &= ~CSIZE;          // Clear all size bits
    tty.c_cflag |= CS8;             // Use 8 bit data
    tty.c_cflag &= ~CRTSCTS;        // Disable RTS/CTS 
    tty.c_cflag |= CREAD | CLOCAL;  // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    // Local Modes
    tty.c_lflag &= ~ICANON;         // Set Canonical
    tty.c_lflag &= ~ECHO;           // Disable echo
    tty.c_lflag &= ~ECHOE;          // Disable erasure
    tty.c_lflag &= ~ECHONL;         // Disable new-line echo
    tty.c_lflag &= ~ISIG;           // Disable interpretation of INTR, QUIT and SUSP

    // Input Modes
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);                             // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);    // Disable any special handling of received bytes

    // Output Modes
    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    // Set Timeouts
    tty.c_cc[VTIME] = 0;    // Min timeout
    tty.c_cc[VMIN] = 0;     // Min number to read

    // Set Baudrate
    cfsetispeed(&tty, baud_rate);
    cfsetospeed(&tty, baud_rate);

    int errno;
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) 
    {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }
}

void UART_Interface::_thread()
{
    uint8_t* data = new uint8_t[BUFFER_SIZE];
    pollfd pollObject;
    pollObject.fd = serial_port;
    pollObject.events = POLLIN | POLLOUT | POLLERR;

	while(thread_active)
	{

		// Poll for actions required
		if (poll(&(pollObject), 1, 0) < 0)
			perror("Poll");

		// Socket Error Occured
		if (pollObject.revents & POLLERR)
		{
			pollObject.revents -= POLLERR;
			_closeDevice();
        }
		
		// Socket ready to read
		if(pollObject.revents & POLLIN)
		{
			pollObject.revents -= POLLIN;
			int retVal = _read(data, BUFFER_SIZE);
            if (retVal > 0)
                RX_BUFFER_PTR.get()->enqueue(data, retVal);
		}

        // Socket ready for write
        int numToWrite = TX_BUFFER_PTR.get()->getDataSize();
        if(numToWrite > 0 && pollObject.revents & POLLOUT)
        {
            TX_BUFFER_PTR.get()->dequeue(data, numToWrite);
            _write(data, numToWrite);
        }
    }

	delete data;
    
}