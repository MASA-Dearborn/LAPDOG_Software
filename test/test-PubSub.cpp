#include <gtest/gtest.h>
#include "broker/broker.h"

using namespace pubsub;

TEST(PubSub, PublisherSingleDataTransfer)
{

    msg::types::TEST_MESSAGE message;
    message.test = 5;

    Subscriber<msg::types::TEST_MESSAGE>* sub = createNewSubscriber(TEST_MESSAGE);
    Publisher<msg::types::TEST_MESSAGE>* pub = createNewPublisher(TEST_MESSAGE);

    pub->publish(&message);

    EXPECT_TRUE(sub->isDataAvailable());
    EXPECT_EQ(sub->getData()->test, 5);
    EXPECT_FALSE(sub->isDataAvailable());

}

TEST(PubSub, PublisherRepeatedDataTransfer)
{

    msg::types::TEST_MESSAGE message;
    message.test = 5;

    Subscriber<msg::types::TEST_MESSAGE>* sub = createNewSubscriber(TEST_MESSAGE);
    Publisher<msg::types::TEST_MESSAGE>* pub = createNewPublisher(TEST_MESSAGE);

    pub->publish(&message);

    EXPECT_TRUE(sub->isDataAvailable());
    EXPECT_EQ(sub->getData()->test, 5);
    EXPECT_FALSE(sub->isDataAvailable());

    message.test = 10;
    pub->publish(&message);

    EXPECT_TRUE(sub->isDataAvailable());
    EXPECT_EQ(sub->getData()->test, 10);
    EXPECT_FALSE(sub->isDataAvailable());

}