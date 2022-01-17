#include <gtest/gtest.h>
#include "IO/MessageHandler.h"
#include "IO/TCP.h"
#include "broker/broker.h"

#include <unistd.h>

class MessageHandlerTest : public ::testing::Test
{
    public:
        virtual void SetUp()
        {
            tcpClient.initClient("127.0.0.1", 9000);
        }

        virtual void TearDown()
        {
            tcpClient.disconnect();
        }

    MessageHandler handler;
    IO::TCPClient tcpClient;

};

TEST_F(MessageHandlerTest, TCPInterfaceTest)
{

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

}