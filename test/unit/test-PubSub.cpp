#include <gtest/gtest.h>
#include "broker/broker.h"

using namespace pubsub;

TEST(PubSub, PublisherSingleDataTransfer)
{

    msg::real::TEST_MESSAGE_READ message;
    message.VAR1 = 5;

    Subscriber<msg::real::TEST_MESSAGE_READ>* sub = createNewSubscriber(TEST_MESSAGE_READ);
    Publisher<msg::real::TEST_MESSAGE_READ>* pub = createNewPublisher(TEST_MESSAGE_READ);

    pub->publish(&message);

    EXPECT_TRUE(sub->isDataAvailable());
    EXPECT_EQ(sub->getDataRef()->VAR1, 5);
    EXPECT_FALSE(sub->isDataAvailable());

    sub->unsubscribe();
    pub->unregister();

}

TEST(PubSub, PublisherRepeatedDataTransfer)
{

    msg::real::TEST_MESSAGE_READ message;
    message.VAR1 = 5;

    Subscriber<msg::real::TEST_MESSAGE_READ>* sub = createNewSubscriber(TEST_MESSAGE_READ);
    Publisher<msg::real::TEST_MESSAGE_READ>* pub = createNewPublisher(TEST_MESSAGE_READ);

    pub->publish(&message);

    EXPECT_TRUE(sub->isDataAvailable());
    EXPECT_EQ(sub->getDataRef()->VAR1, 5);
    EXPECT_FALSE(sub->isDataAvailable());

    message.VAR1 = 10;
    pub->publish(&message);

    EXPECT_TRUE(sub->isDataAvailable());
    EXPECT_EQ(sub->getDataRef()->VAR1, 10);
    EXPECT_FALSE(sub->isDataAvailable());

    sub->unsubscribe();
    pub->unregister();

}

TEST(PubSub, PublisherMultipleDataTransfer)
{

    msg::real::TEST_MESSAGE_READ message;
    message.VAR1 = 5;

    Subscriber<msg::real::TEST_MESSAGE_READ>* sub1 = createNewSubscriber(TEST_MESSAGE_READ);
    Subscriber<msg::real::TEST_MESSAGE_READ>* sub2 = createNewSubscriber(TEST_MESSAGE_READ);
    Publisher<msg::real::TEST_MESSAGE_READ>* pub = createNewPublisher(TEST_MESSAGE_READ);

    pub->publish(&message);

    EXPECT_TRUE(sub1->isDataAvailable());
    EXPECT_EQ(sub1->getDataRef()->VAR1, 5);
    EXPECT_FALSE(sub1->isDataAvailable());

    EXPECT_TRUE(sub2->isDataAvailable());
    EXPECT_EQ(sub2->getDataRef()->VAR1, 5);
    EXPECT_FALSE(sub2->isDataAvailable());

    sub1->unsubscribe();
    sub2->unsubscribe();
    pub->unregister();

}

TEST(PubSub, MultiplePublishers)
{

    msg::real::TEST_MESSAGE_READ message;
    message.VAR1 = 5;

    Publisher<msg::real::TEST_MESSAGE_READ>* pub1 = createNewPublisher(TEST_MESSAGE_READ);
    Publisher<msg::real::TEST_MESSAGE_READ>* pub2 = createNewPublisher(TEST_MESSAGE_READ);
    Subscriber<msg::real::TEST_MESSAGE_READ>* sub = createNewSubscriber(TEST_MESSAGE_READ);

    pub1->publish(&message);

    EXPECT_TRUE(sub->isDataAvailable());
    EXPECT_EQ(sub->getDataRef()->VAR1, 5);
    EXPECT_FALSE(sub->isDataAvailable());

    message.VAR1 = 10;
    pub2->publish(&message);

    EXPECT_TRUE(sub->isDataAvailable());
    EXPECT_EQ(sub->getDataRef()->VAR1, 10);
    EXPECT_FALSE(sub->isDataAvailable());

    sub->unsubscribe();
    pub1->unregister();
    pub2->unregister();

}