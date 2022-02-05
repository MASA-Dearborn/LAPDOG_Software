#include "IO/SPI_Operations.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

char _spi_read_byte(int fileDescriptor)
{

}

void _spi_write_byte(int fileDescriptor, char byte)
{

}

void _spi_half_read(int fileDescriptor, char* dest, const uint32_t num)
{

}

void _spi_half_write(int fileDescriptor, char* src, const uint32_t num)
{

}
