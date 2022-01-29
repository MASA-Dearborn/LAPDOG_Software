#pragma once

#include <thread>
#include <vector>

#include "IOInterface.h"

namespace IO
{

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
            void _openDevice();
            void _closeDevice();

            void _thread();
            std::thread m_threadObj;
            bool m_threadActive = true;

            const char* m_deviceName;
            int m_fileDescriptor;
    };

};