#include <gtest/gtest.h>
#include "broker/broker.h"

using namespace pubsub;

TEST(PubSub, PublisherSingleDataTransfer)
{

    msg::real::TEST_MESSAGE message;
    message.test = 5;

    Subscriber<msg::real::TEST_MESSAGE>* sub = createNewSubscriber(TEST_MESSAGE);
    Publisher<msg::real::TEST_MESSAGE>* pub = createNewPublisher(TEST_MESSAGE);

    pub->publish(&message);

    EXPECT_TRUE(sub->isDataAvailable());
    EXPECT_EQ(sub->getData()->test, 5);
    EXPECT_FALSE(sub->isDataAvailable());

    sub->unsubscribe();
    pub->unregister();

}

TEST(PubSub, PublisherRepeatedDataTransfer)
{

    msg::real::TEST_MESSAGE message;
    message.test = 5;

    Subscriber<msg::real::TEST_MESSAGE>* sub = createNewSubscriber(TEST_MESSAGE);
    Publisher<msg::real::TEST_MESSAGE>* pub = createNewPublisher(TEST_MESSAGE);

    pub->publish(&message);

    EXPECT_TRUE(sub->isDataAvailable());
    EXPECT_EQ(sub->getData()->test, 5);
    EXPECT_FALSE(sub->isDataAvailable());

    message.test = 10;
    pub->publish(&message);

    EXPECT_TRUE(sub->isDataAvailable());
    EXPECT_EQ(sub->getData()->test, 10);
    EXPECT_FALSE(sub->isDataAvailable());

    sub->unsubscribe();
    pub->unregister();

}

TEST(PubSub, PublisherMultipleDataTransfer)
{

    msg::real::TEST_MESSAGE message;
    message.test = 5;

    Subscriber<msg::real::TEST_MESSAGE>* sub1 = createNewSubscriber(TEST_MESSAGE);
    Subscriber<msg::real::TEST_MESSAGE>* sub2 = createNewSubscriber(TEST_MESSAGE);
    Publisher<msg::real::TEST_MESSAGE>* pub = createNewPublisher(TEST_MESSAGE);

    pub->publish(&message);

    EXPECT_TRUE(sub1->isDataAvailable());
    EXPECT_EQ(sub1->getData()->test, 5);
    EXPECT_FALSE(sub1->isDataAvailable());

    EXPECT_TRUE(sub2->isDataAvailable());
    EXPECT_EQ(sub2->getData()->test, 5);
    EXPECT_FALSE(sub2->isDataAvailable());

    sub1->unsubscribe();
    sub2->unsubscribe();
    pub->unregister();

}

TEST(PubSub, MultiplePublishers)
{

    msg::real::TEST_MESSAGE message;
    message.test = 5;

    Publisher<msg::real::TEST_MESSAGE>* pub1 = createNewPublisher(TEST_MESSAGE);
    Publisher<msg::real::TEST_MESSAGE>* pub2 = createNewPublisher(TEST_MESSAGE);
    Subscriber<msg::real::TEST_MESSAGE>* sub = createNewSubscriber(TEST_MESSAGE);

    pub1->publish(&message);

    EXPECT_TRUE(sub->isDataAvailable());
    EXPECT_EQ(sub->getData()->test, 5);
    EXPECT_FALSE(sub->isDataAvailable());

    message.test = 10;
    pub2->publish(&message);

    EXPECT_TRUE(sub->isDataAvailable());
    EXPECT_EQ(sub->getData()->test, 10);
    EXPECT_FALSE(sub->isDataAvailable());

    sub->unsubscribe();
    pub1->unregister();
    pub2->unregister();

}