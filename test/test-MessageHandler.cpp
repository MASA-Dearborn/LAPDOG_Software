#include <gtest/gtest.h>
#include "IO/MessageHandler.h"
#include "IO/TCP.h"
#include "broker/broker.h"

#include <unistd.h>



TEST(MessageHandlerTest, PublishAndSendTest)
{

    MessageHandler handler;

    pubsub::Subscriber<msg::real::TEST_MESSAGE>* sub = createNewSubscriber(TEST_MESSAGE);
    pubsub::Publisher<msg::real::TEST_MESSAGE_2>* pub = createNewPublisher(TEST_MESSAGE_2);
    IO::GenericInterface* interface = new IO::GenericInterface();

    handler.attachIOInterface(interface);

    msg::real::TEST_MESSAGE_2 returned_output;
    msg::real::TEST_MESSAGE_2 output;
    output.VAR1 = 10;
    output.VAR2 = 30.4992676;
    
    pub->publish(&output);
    usleep(1000);

    returned_output = *((msg::real::TEST_MESSAGE_2*)interface->getTXBuffer());
    EXPECT_EQ(output.id, returned_output.id);
    EXPECT_EQ(output.size, returned_output.size);
    EXPECT_EQ(output.VAR1, returned_output.VAR1);
    EXPECT_EQ(output.VAR2, returned_output.VAR2);

    handler.~MessageHandler();
    sub->unsubscribe();
    pub->unregister();

}

TEST(MessageHandlerTest, TCPInterfaceTest)
{

    MessageHandler handler;
    IO::TCPClient tcpClient;
    tcpClient.initClient("127.0.0.1", LISTEN_PORT);

    pubsub::Subscriber<msg::real::TEST_MESSAGE>* sub = createNewSubscriber(TEST_MESSAGE);
    EXPECT_FALSE(sub->isDataAvailable());

    msg::real::TEST_MESSAGE tempReal;
    tempReal.test = 20;
    tempReal.VAR2 = 30.4992676;

    msg::raw::TEST_MESSAGE tempRaw = msg::conv::TEST_MESSAGE_TO_RAW(&tempReal);

    tcpClient.write((char*)(&tempRaw), sizeof(msg::raw::TEST_MESSAGE));

    while(!sub->isDataAvailable());

    EXPECT_TRUE(sub->isDataAvailable());
    
    msg::real::TEST_MESSAGE retVal = *(sub->getData());

    EXPECT_EQ(tempReal.id, retVal.id);
    EXPECT_EQ(tempReal.size, retVal.size);
    EXPECT_EQ(tempReal.test, retVal.test);
    EXPECT_EQ(tempReal.VAR2, retVal.VAR2);

    sub->unsubscribe();
    tcpClient.disconnect();

}