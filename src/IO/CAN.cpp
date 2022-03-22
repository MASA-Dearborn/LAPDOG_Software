#include "IO/CAN.h"
#include "messageTypes.h"

#include <stdio.h>
#include <algorithm>
#include <unistd.h>

using namespace IO;

CAN_Interface::CAN_Interface() : IOInterface(TYPE_CAN)
{
    /* Initialize Buffers */
    if (initBuffers() < 0)
		return;

    _openSocketCAN();

    /* Setup the Timer */
    io_event_data.ref = this;
    io_event_data.time_count = 0;
    io_timer.setHandler((void (*)(union sigval))&_can_io_handler);
    io_timer.setHandlerDataPointer(&io_event_data);
    io_timer.setIntervalMilliseconds(CAN_IO_INTERVAL_BASE_MS);
    io_timer.setStartDelayMilliseconds(CAN_IO_INTERVAL_BASE_MS);
    io_timer.startTimer();
}

CAN_Interface::~CAN_Interface()
{
    shutdown(can_socket_id, SHUT_RDWR);
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
    int retval = 0;
    struct ifreq ifr;

    can_socket_id = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (can_socket_id < 0)
    {
        perror("CAN");
        exit(0);
    }

    strcpy(ifr.ifr_name, "can0");
    retval = ioctl(can_socket_id, SIOCGIFINDEX, &ifr);
    if (retval < 0)
    {
        perror("CAN");
        exit(0);
    }

    address.can_family = AF_CAN;
    address.can_ifindex = ifr.ifr_ifindex;

    retval = bind(can_socket_id, (struct sockaddr*)&address, sizeof(address));
    if (retval < 0)
    {
        perror("CAN");
        exit(0);
    }
}

void IO::_can_io_handler(union sigval data)
{
    can_timer_data* args = (can_timer_data*)data.sival_ptr;
    CAN_Interface* obj = (CAN_Interface*)args->ref;
    static uint8_t data_buffer[1024];
    
    struct pollfd pollObject { .fd = obj->can_socket_id,
                               .events = POLLIN | POLLOUT | POLLERR, };

    poll(&pollObject, 1, 0);

    /* Handle Errors */
    if (pollObject.revents & POLLERR)
	{
		pollObject.revents -= POLLERR;
		printf("CAN: Error Event\n");
        return;
	}

    /* Write Message if one is available */
    if ((pollObject.revents & POLLOUT) && (obj->TX_BUFFER_PTR.get()->getDataSize() > 0)) 
    {
        obj->_can_write();
        pollObject.revents -= POLLOUT;
    }

    /* Read Message */
    if (pollObject.revents & POLLIN) 
    {
        obj->_can_read();
        printf("CAN_Recv\n");
        pollObject.revents -= POLLIN;
    }

}