#pragma once

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <thread>

#include "IOInterface.h"

namespace IO
{

    class UART_Interface : public IOInterface
    {
        public:
            UART_Interface();
            UART_Interface(const char* dev_name, speed_t baud_rate);
            ~UART_Interface();

            // Inherited from IOInterface
            int readMessage(uint8_t* dest, const int num);
            int writeMessage(uint8_t* src, const int num);

        protected:
            int _write(uint8_t* src, const int num);
            int _read(uint8_t* dest, const int num);

            void _openDevice();
            void _closeDevice();
            void _configDevice();
            void _thread();

            std::thread threadObj;
            bool thread_active = true;

            const char* device_name;
            speed_t baud_rate;
            int serial_port;
            struct termios tty;
    };

};