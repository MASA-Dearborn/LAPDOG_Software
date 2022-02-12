#include "IO/CAN.h"
#include "messageTypes.h"

#include <stdio.h>
#include <algorithm>
#include <unistd.h>

using namespace IO;

CAN_Interface::CAN_Interface()
{

}

CAN_Interface::~CAN_Interface()
{

}

int CAN_Interface::readMessage(uint8_t* dest, const int num)
{
    return RX_BUFFER_PTR.get()->dequeue(dest, num);
}

int CAN_Interface::writeMessage(uint8_t* src, const int num)
{
    return TX_BUFFER_PTR.get()->enqueue(src, num);
}

int CAN_Interface::_can_read()
{
    uint8_t buffer[128] = {0};
    msg::GENERIC_MESSAGE* fake_msg = (msg::GENERIC_MESSAGE*)&buffer;
    struct can_frame frame;
    int retval;

    /* Read the can frame */
    retval = read(can_socket_id, &frame, sizeof(struct can_frame));
    if (retval < 0) {
        perror("CAN Socket Read");
        return -1;
    }

    /* Copy CAN frame into buffer with message format */
    fake_msg->id = (msg::id::MessageType)frame.can_id;
    fake_msg->size = sizeof(msg::GENERIC_MESSAGE) + frame.can_dlc;
    memcpy(frame.data, &buffer[sizeof(msg::GENERIC_MESSAGE)], frame.can_dlc);

    RX_BUFFER_PTR.get()->enqueue(buffer, fake_msg->size);
    return retval;
}

int CAN_Interface::_can_write()
{
    int retval;
    uint8_t buffer[128] = {0};
    struct can_frame frame;
    msg::GENERIC_MESSAGE* message;

    /* Get GENERIC_MESSAGE from TX queue */
    message = (msg::GENERIC_MESSAGE*)TX_BUFFER_PTR.get()->peek();
    TX_BUFFER_PTR.get()->dequeue(buffer, message->size);
    message = (msg::GENERIC_MESSAGE*)buffer;

    /* Setup CAN frame */
    frame.can_id = message->id;
    frame.can_dlc = message->size - sizeof(msg::GENERIC_MESSAGE);
    memcpy(&buffer[sizeof(msg::GENERIC_MESSAGE)], frame.data, frame.can_dlc);

    /* Write the frame */
    retval = write(can_socket_id, &frame, sizeof(struct can_frame));
    if (retval < 0) {
        perror("CAN Socket Write");
        return -1;
    }

    return retval;
}

void CAN_Interface::_openSocketCAN()
{
    struct ifreq ifr;

    can_socket_id = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    strcpy(ifr.ifr_name, "can0");
    ioctl(can_socket_id, SIOCGIFINDEX, &ifr);

    address.can_family = AF_CAN;
    address.can_ifindex = ifr.ifr_ifindex;

    bind(can_socket_id, (struct sockaddr*)&address, sizeof(address));
}
