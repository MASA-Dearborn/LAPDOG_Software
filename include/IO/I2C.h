#pragma once

#include <thread>
#include <vector>
#include <linux/i2c-dev.h>

#include "IOInterface.h"

namespace IO
{

    struct I2C_Slave_Message
    {
        long slave_address;
        void (*read_function)(int, char*, int); // file_id, data_buffer, size_of_buffer
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

        protected:
            void _init();
            void _openDevice();
            void _closeDevice();
            void _registerMessageOperation(long slave_address, void (*read_function)(int, char*, int));

            void _thread();
            std::thread m_threadObj;
            bool m_threadActive = true;

            std::vector<I2C_Slave_Message> m_slaveMessageOperations;
            const char* m_deviceName;
            int m_fileDescriptor;
    };

    static void _i2c_read(int fileDescriptor, char* dest, const uint32_t num);
    static void _i2c_write(int fileDescriptor, uint32_t reg, char* src, const uint32_t num);
    static void _i2c_set_slave_address(int fileDescriptor, long slave_address);

};