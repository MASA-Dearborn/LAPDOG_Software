#pragma once

#include <cstdint>

namespace IO
{

    // Pure Virtual interface class
    class IOInterface
    {
    public:

        // IO Interaction Methods
        virtual int read(const void* dest, const int num) = 0;
        virtual int write(const void* src, const int num) = 0;

        // Internal State Methods
        virtual int getReadableAmount() = 0;
        virtual int getWriteSpaceAvailable() = 0;

    };

}