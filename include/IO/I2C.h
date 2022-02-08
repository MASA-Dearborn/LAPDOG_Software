#pragma once

#include <thread>
#include <vector>

#include "IOInterface.h"
#include "timer.h"

#define I2C_IO_INTERVAL_BASE_MS 10

namespace IO
{

    void _i2c_io_handler(union sigval data);

    struct I2C_Slave_Message
    {
        uint64_t interval_ms = 0;
        uint64_t last_trigger = 0;
        long slave_address;
        void (*read_function)(int, int, char*, int); // file_id, slave_address, data_buffer, size_of_buffer
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
            I2C_Interface(const char* dev_name);
            ~I2C_Interface();

            // Inherited from IOInterface
            int readMessage(uint8_t* dest, const int num);
            int writeMessage(uint8_t* src, const int num);
            friend void _i2c_io_handler(union sigval data);

        protected:
            void _init();
            void _openDevice();
            void _closeDevice();
            void _registerMessageOperation(long slave_address, int interval_ms, void (*read_function)(int, int, char*, int));

            /* IO Handling Data */
            Timer io_timer;
            i2c_timer_data io_event_data;

            std::vector<I2C_Slave_Message> m_slaveMessageOperations;
            const char* m_deviceName;
            int m_fileDescriptor;
    };

};