#include "IO/MessageHandler.h"
#include "broker/broker.h"
#include "IO/I2C.h"

#include <unistd.h>
#include <cstdio>

using namespace IO;

int main()
{

    /*
    MessageHandler* test = new MessageHandler();
    Subscriber<msg::real::TEST_MESSAGE>* sub = createNewSubscriber(TEST_MESSAGE);

    while (true)
    {
        if(sub->isDataAvailable())
        {
            printf("Pushed data\n");
            sub->getData();
        }
        usleep(1000);
    }
    */

   I2C_Interface temp("/dev/i2c-1");

   while(true)
   {
       usleep(1000);
   }

}