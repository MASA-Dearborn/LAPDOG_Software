#include "IO/SPI.h"

int _spi_read_byte(int fileDescriptor, char* location);
int _spi_write_byte(int fileDescriptor, char byte);
int _spi_half_read(int fileDescriptor, char* dest, const uint32_t num);
int _spi_half_write(int fileDescriptor, char* src, const uint32_t num);