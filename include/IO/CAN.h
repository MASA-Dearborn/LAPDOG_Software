/**
 * @file    CAN.h
 * @author  Lucas Ringe (lringe@umich.edu)
 * @brief   Implements Socket CAN as described by https://www.kernel.org/doc/html/latest/networking/can.html
 * @version 0.1
 * @date    2022-02-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include "IOInterface.h"
#include "timer.h"

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <poll.h>

#define CAN_IO_INTERVAL_BASE_MS 10

namespace IO
{

    void _can_io_handler(union sigval data);

    struct can_timer_data
    {
        uint64_t time_count = 0;
        IOInterface* ref = nullptr;
    };

    class CAN_Interface : public IOInterface
    {
        public:
            CAN_Interface();
            CAN_Interface(const char* device_name);
            ~CAN_Interface();

            int readMessage(uint8_t* dest, const int num);
            int writeMessage(uint8_t* src, const int num);

        protected:
            int _can_read();
            int _can_write();
            void _openSocketCAN(const char* device_name);
            friend void _can_io_handler(union sigval data);

            /* IO Handling Data */
            Timer io_timer;
            can_timer_data io_event_data;

            /* CAN Data */
            int can_socket_id;
            struct sockaddr_can address;
    };

};