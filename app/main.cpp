#include "IO/MessageHandler.h"
#include "broker/broker.h"
#include "IO/SPI.h"
#include "IO/I2C.h"

#include <unistd.h>
#include <cstdio>

using namespace IO;

int main()
{

    SPI_Interface temp_spi;
    I2C_Interface temp_i2c;

    while(true)
    {
        usleep(1000000);
    }

}