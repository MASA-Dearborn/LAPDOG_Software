#include "IO/MessageHandler.h"
#include "broker/broker.h"

#include <cstdio>

using namespace pubsub;

int main()
{

    MessageHandler* test = new MessageHandler();

    Subscriber<msg::real::TEST_MESSAGE>* sub = createNewSubscriber(TEST_MESSAGE);

    while (true)
    {
        if(sub->isDataAvailable())
        {
            printf("Pushed data\n");
            sub->getData();
        }
    }
}