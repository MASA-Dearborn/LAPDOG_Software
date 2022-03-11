#pragma once

#include <thread>
#include <vector>

#include "IOInterface.h"
#include "timer.h"

#define MAX_I2C_DEVICES         16
#define MAX_I2C_OPERATIONS      32
#define I2C_IO_INTERVAL_BASE_MS 10

namespace IO
{

    void _i2c_io_handler(union sigval data);

    enum I2C_OperationType
    {
        I2C_WRITE,
        I2C_READ
    };

    struct I2C_Slave_Message
    {
        uint64_t interval_ms = 0;
        uint64_t last_trigger = 0;
        msg::id::MessageType msg_type = msg::id::UNDEFINED_MESSAGE;
        void (*function)(int, int, msg::GENERIC_MESSAGE*) = nullptr; // file_id, slave_address 
    };

    struct i2c_device
    {
        char name[64];
        char device_file[64];
        int file_descriptor = -1;
        int slave_address = 0;
        uint8_t num_read_operations = 0;
        uint8_t num_write_operations = 0;
        std::array<I2C_Slave_Message, MAX_I2C_OPERATIONS> read_operations;
        std::array<I2C_Slave_Message, MAX_I2C_OPERATIONS> write_operations;
    };

    struct i2c_timer_data
    {
        uint64_t time_count = 0;
        IOInterface* ref = nullptr;
    };

    class I2C_Interface : public IOInterface
    {
        public:
            I2C_Interface();
            ~I2C_Interface();

            // Inherited from IOInterface
            int readMessage(uint8_t* dest, const int num);
            int writeMessage(uint8_t* src, const int num);
            friend void _i2c_io_handler(union sigval data);

        protected:
            void _init();
            void _openDevice(i2c_device& device);
            void _closeDevice(i2c_device& device);
            void _registerDevice(const char* name, const char* device_file, int slave_address);
            void _registerOperation(const char* device_name, I2C_OperationType type, msg::id::MessageType msg_id, int interval_ms, void (*func)(int, int, msg::GENERIC_MESSAGE*));
            void _registerInitFunction(const char* device_name, void (*func)(int, int, msg::GENERIC_MESSAGE*));

            /* IO Handling Data */
            Timer io_timer;
            i2c_timer_data io_event_data;

            int device_count = 0;
            std::array<i2c_device, MAX_I2C_DEVICES> devices;
    };

};