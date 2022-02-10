#pragma once

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <thread>
#include <array>

#include "IOInterface.h"
#include "timer.h"

#define MAX_UART_DEVICES         8
#define UART_IO_INTERVAL_BASE_MS 10

namespace IO
{

    void _uart_io_handler(union sigval data);

    struct uart_device
    {
        char name[64];
        char device_file[64];
        int file_descriptor = -1;
        speed_t baud_rate;
        struct termios tty;
        std::array<bool, msg::id::META_NUM_MESSAGES> writeable_messages = {false}; 
    };

    struct uart_timer_data
    {
        uint64_t time_count = 0;
        IOInterface* ref = nullptr;
    };

    class UART_Interface : public IOInterface
    {
        public:
            UART_Interface();
            ~UART_Interface();

            // Inherited from IOInterface
            int readMessage(uint8_t* dest, const int num);
            int writeMessage(uint8_t* src, const int num);

        protected:

            void _init();
            void _registerDevice(const char* name, const char* device_file, speed_t baud);
            void _deviceAddWriteableMessage(const char* device_name, msg::id::MessageType type);
            void _openDevice(uart_device& device);
            void _closeDevice(uart_device& device);
            void _configDevice(uart_device& device, speed_t baud);
            friend void _uart_io_handler(union sigval data);

            Timer io_timer;
            uart_timer_data io_event_data;

            char device_count = 0;
            std::array<uart_device, MAX_UART_DEVICES> devices;

    };

};