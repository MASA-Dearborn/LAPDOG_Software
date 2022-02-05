#include "IO/MessageHandler.h"
#include "broker/broker.h"
#include "IO/I2C.h"
#include "timer.h"

#include <unistd.h>
#include <cstdio>

using namespace IO;

struct event_data {
    long time = 0;
};

void print(union sigval timer_data)
{
    event_data* data = (event_data*)timer_data.sival_ptr;
    data->time += 10;
    printf("%08d\n", data->time);
}

int main()
{

    event_data test;
    Timer timer(&print, &test, 10, 1);

    while(true)
    {
        usleep(1000000);
    }

}