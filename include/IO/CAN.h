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
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <poll.h>


namespace IO
{

    class CAN_Interface : public IOInterface
    {
        public:
            CAN_Interface();
            ~CAN_Interface();

            int readMessage(uint8_t* dest, const int num);
            int writeMessage(uint8_t* src, const int num);

        protected:
            int _can_read();
            int _can_write();
            void _openSocketCAN();

            int can_socket_id;
            struct sockaddr_can address;
    };

};