#include "messageTypes.h"
#include "timer.h"
#include <cstdint>

namespace i2c_operations
{

    struct callback_data
    {
        int fileDescriptor;
        int slave_address;
        msg::GENERIC_MESSAGE* msg;
    };

    // Read functions
    void ALTIMETER_READ_CONFIG(int fileDescriptor, int slave_address, msg::GENERIC_MESSAGE* msg);
    void ALTIMETER_READ_ALTITUDE(int fileDescriptor, int slave_address, msg::GENERIC_MESSAGE* msg);

    // Delayed callback functions
    void ALTIMETER_READ_ALTITUDE_CALLBACK(sigval data);
}