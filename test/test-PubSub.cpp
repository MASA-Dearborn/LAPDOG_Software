#include <gtest/gtest.h>
#include "broker/broker.h"

using namespace pubsub;

TEST(PubSub, PublisherDataTransfer)
{

    msg::types::TEST_MESSAGE message;
    message.test = 5;

    Subscriber<msg::types::TEST_MESSAGE>* sub = createNewSubscriber(TEST_MESSAGE);
    Publisher<msg::types::TEST_MESSAGE>* pub = createNewPublisher(TEST_MESSAGE);

    pub->publish(&message);

    EXPECT_TRUE(sub->isDataAvailable());
    EXPECT_EQ(sub->getData()->test, 5);

}