#include "IO/SPI_Operations.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

int _spi_read_byte(int fileDescriptor, char* location)
{   
    if (read(fileDescriptor, location, 1) == 0);
        return -1;
    
    return 1;
}

int _spi_write_byte(int fileDescriptor, char byte)
{
    return write(fileDescriptor, &byte, 1);
}

int _spi_half_read(int fileDescriptor, char* dest, const uint32_t num)
{
    if (dest == nullptr)
        return -1;

    return read(fileDescriptor, dest, num);
}

int _spi_half_write(int fileDescriptor, char* src, const uint32_t num)
{
    if (src == nullptr)
        return -1;

    return write(fileDescriptor, src, num);
}
