#include <gtest/gtest.h>
#include "broker/broker.h"

using namespace pubsub;

TEST(Subscriber, SubscriberCreation)
{
    // Data Creation
    msg::types::TEST_MESSAGE TEST_MESSAGE;
    TEST_MESSAGE.test = 5;

    // Create subscriber into generic object & setup object
    Subscriber<msg::types::TEST_MESSAGE>* sub = createNewSubscriber(TEST_MESSAGE);
    sub->setDataPointer(&TEST_MESSAGE);
    sub->setDataAvailable();

    // Verify ID correct
    EXPECT_EQ(sub->getType(), msg::ids::TEST_MESSAGE);
    EXPECT_TRUE(sub->isDataAvailable());
    EXPECT_EQ(sub->getData()->test, 5);
    EXPECT_EQ(DataBroker.getNumSubscribers(msg::ids::TEST_MESSAGE), 1);

    sub->unsubscribe();

}

TEST(Subscriber, SubscriberRegistration)
{

    Subscriber<msg::types::TEST_MESSAGE>* sub = createNewSubscriber(TEST_MESSAGE);

    EXPECT_EQ(DataBroker.getNumSubscribers(msg::ids::TEST_MESSAGE), 1);
    EXPECT_EQ(sub->getData()->test, 0);

    sub->unsubscribe();

}