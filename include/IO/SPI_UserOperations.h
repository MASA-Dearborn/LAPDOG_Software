#pragma once

#include "IO/IOInterface.h"
#include "messageTypes.h"
#include "timer.h"
#include <cstdint>

namespace spi_operations
{
    struct callback_data
    {
        int fileDescriptor;
        IO::IOInterface* obj;
    };

    

}