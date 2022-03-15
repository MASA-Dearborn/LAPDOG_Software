#include <gtest/gtest.h>
#include "IO/MessageHandler.h"
#include "IO/TCP.h"
#include "broker/broker.h"

#include <unistd.h>



TEST(MessageHandlerTest, PublishAndSendTest)
{

    MessageHandler handler;

    pubsub::Subscriber<msg::real::TEST_MESSAGE_READ>* sub = createNewSubscriber(TEST_MESSAGE_READ);
    pubsub::Publisher<msg::real::TEST_MESSAGE_WRITE>* pub = createNewPublisher(TEST_MESSAGE_WRITE);
    IO::GenericInterface* interface = new IO::GenericInterface();

    defaultMessageHandlerSetup(handler);
    handler.attachIOInterface(interface);

    msg::real::TEST_MESSAGE_WRITE output;
    msg::raw::TEST_MESSAGE_WRITE returned_output;
    msg::RealMessageUnion converted_message;
    output.VAR1 = 10;
    output.VAR2 = 30.4992676;
    
    pub->publish(&output);
    sched_yield();
    usleep(1000);

    returned_output = *((msg::raw::TEST_MESSAGE_WRITE*)interface->getTXBuffer());
    msg::conv::convertRawToReal(&converted_message, &returned_output);
    EXPECT_EQ(output.id, converted_message.TEST_MESSAGE_WRITE.id);
    EXPECT_EQ(output.size, converted_message.TEST_MESSAGE_WRITE.size);
    EXPECT_EQ(output.VAR1, converted_message.TEST_MESSAGE_WRITE.VAR1);
    EXPECT_EQ(output.VAR2, converted_message.TEST_MESSAGE_WRITE.VAR2);

    sub->unsubscribe();
    pub->unregister();
}

/*
TEST(MessageHandlerTest, TCPInterfaceTest)
{
    MessageHandler handler;
    IO::TCPClient tcpClient;
    defaultMessageHandlerSetup(handler);
    handler.attachIOInterface(new IO::TCP_Interface());

    usleep(100);
    tcpClient.initClient("127.0.0.1", LISTEN_PORT);

    pubsub::Subscriber<msg::real::TEST_MESSAGE_READ>* sub = createNewSubscriber(TEST_MESSAGE_READ);
    EXPECT_FALSE(sub->isDataAvailable());

    msg::real::TEST_MESSAGE_READ tempReal;
    tempReal.VAR1 = 20;
    tempReal.VAR2 = 30.4992676;

    msg::raw::TEST_MESSAGE_READ tempRaw = msg::conv::TEST_MESSAGE_READ_TO_RAW(&tempReal);

    tcpClient.write((char*)(&tempRaw), sizeof(msg::raw::TEST_MESSAGE_READ));

    while(!sub->isDataAvailable());

    EXPECT_TRUE(sub->isDataAvailable());
    
    msg::real::TEST_MESSAGE_READ retVal = *(sub->getDataRef());

    EXPECT_EQ(tempReal.id, retVal.id);
    EXPECT_EQ(tempReal.size, retVal.size);
    EXPECT_EQ(tempReal.VAR1, retVal.VAR1);
    EXPECT_EQ(tempReal.VAR2, retVal.VAR2);

    sub->unsubscribe();
    tcpClient.disconnect();
}
*/