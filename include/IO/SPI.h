/**
 * @file        SPI.h
 * @author      Lucas Ringe (lringe@umich.edu)
 * @brief       Contains all interfacing classes and data structures for SPI communication
 * @version     0.1
 * @date        2022-02-04
 * @copyright   Copyright (c) 2022
 * 
 * @note        To add a SPI device, use the _registerDevice() function inside the _init() function.
 *              To add a new read or write operation, use _registerOperation() in _init() and declare 
 *              the function in SPI_Operations.h and define  in SPI_Operations.cpp
 */

#pragma once
#include <thread>
#include <array>

#include "timer.h"
#include "IOInterface.h"

#define MAX_SPI_DEVICES         16
#define MAX_SPI_OPERATIONS      32
#define SPI_IO_INTERVAL_BASE_MS 10


namespace IO
{

    // int example_read(int file_id, msg::GENERIC_MESSAGE* message);
    void _spi_io_handler(union sigval data);

    enum SPI_OperationType
    {
        SPI_WRITE,
        SPI_READ
    };

    struct SPI_Slave_Message
    {
        uint64_t interval_ms = 0; // unused
        uint64_t last_trigger = 0;
        msg::id::MessageType msg_type = msg::id::UNDEFINED_MESSAGE;
        int (*function)(int, msg::GENERIC_MESSAGE*) = nullptr; // file_id, generic_message
    };

    struct spi_device
    {
        char name[64];
        char device_file[64];
        int file_descriptor = -1;
        uint8_t num_read_operations = 0;
        uint8_t num_write_operations = 0;
        std::array<SPI_Slave_Message, MAX_SPI_OPERATIONS> read_operations;
        std::array<SPI_Slave_Message, MAX_SPI_OPERATIONS> write_operations;
    };

    struct spi_timer_data
    {
        uint64_t time_count = 0;
        IOInterface* ref = nullptr;
    };

    class SPI_Interface : public IOInterface
    {
        public:
            SPI_Interface();
            ~SPI_Interface();

            // Inherited from IOInterface
            int readMessage(uint8_t* dest, const int num);
            int writeMessage(uint8_t* src, const int num);
            friend void _spi_io_handler(union sigval data);

        protected:
            void _init();
            void _openDevice(spi_device& device);
            void _closeDevice(spi_device& device);
            void _registerDevice(const char* name, const char* device_file);
            void _registerOperation(const char* device_name, SPI_OperationType type, int interval_ms, int (*func)(int, msg::GENERIC_MESSAGE*));

            /* IO Handling Data */
            Timer io_timer;
            spi_timer_data io_event_data;

            int device_count = 0;
            std::array<spi_device, MAX_SPI_DEVICES> devices;
    };

};