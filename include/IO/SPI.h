#pragma once
#include <thread>
#include <array>
#include "IOInterface.h"

#ifndef MAX_SPI_DEVICES
    #define MAX_SPI_DEVICES 16
#endif

#ifndef MAX_SPI_OPERATIONS
    #define MAX_SPI_OPERATIONS 32
#endif

namespace IO
{

    int example_read(int file_id, msg::GENERIC_MESSAGE* message);

    enum SPI_OperationType
    {
        SPI_WRITE,
        SPI_READ
    };

    struct SPI_Slave_Message
    {
        int interval_ms = -1; // unused
        int (*function)(int, msg::GENERIC_MESSAGE*) = nullptr; // file_id, generic_message
    };

    struct spi_device
    {
        char name[64];
        char device_file_name[64];
        int file_descriptor = -1;
        std::array<SPI_Slave_Message, MAX_SPI_OPERATIONS> read_operations;
        std::array<SPI_Slave_Message, MAX_SPI_OPERATIONS> write_operations;
    };

    class SPI_Interface : public IOInterface
    {
        public:
            SPI_Interface();
            SPI_Interface(const char* dev_name);
            ~SPI_Interface();

            // Inherited from IOInterface
            int readMessage(uint8_t* dest, const int num);
            int writeMessage(uint8_t* src, const int num);

        protected:
            void _init();
            void _openDevice(spi_device& device);
            void _closeDevice(spi_device& device);
            void _registerDevice(const char* name, const char* device_file);
            void _registerOperation(const char* device, SPI_OperationType type, int interval_ms, int*(int, msg::GENERIC_MESSAGE));

            /* Thread Data */
            void _thread();
            std::thread m_threadObj;
            bool m_threadActive = true;

            int device_count = 0;
            std::array<spi_device, MAX_SPI_DEVICES> devices;

    };

};