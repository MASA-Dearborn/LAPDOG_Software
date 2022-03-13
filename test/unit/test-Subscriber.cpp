#include <gtest/gtest.h>
#include "broker/broker.h"

using namespace pubsub;

TEST(Subscriber, SubscriberCreation)
{
    // Data Creation
    msg::real::TEST_MESSAGE_READ TEST_MESSAGE_READ;
    TEST_MESSAGE_READ.VAR1 = 5;

    // Create subscriber into generic object & setup object
    Subscriber<msg::real::TEST_MESSAGE_READ>* sub = createNewSubscriber(TEST_MESSAGE_READ);
    sub->setDataPointer(&TEST_MESSAGE_READ);
    sub->setDataAvailable();

    // Verify ID correct
    EXPECT_EQ(sub->getType(), msg::id::TEST_MESSAGE_READ);
    EXPECT_TRUE(sub->isDataAvailable());
    EXPECT_EQ(sub->getData()->VAR1, 5);
    EXPECT_EQ(DataBroker.getNumSubscribers(msg::id::TEST_MESSAGE_READ), 1);

    sub->unsubscribe();

}

TEST(Subscriber, SubscriberRegistration)
{

    Subscriber<msg::real::TEST_MESSAGE_READ>* sub = createNewSubscriber(TEST_MESSAGE_READ);

    EXPECT_EQ(DataBroker.getNumSubscribers(msg::id::TEST_MESSAGE_READ), 1);
    EXPECT_EQ(sub->getData()->VAR1, 10);

    sub->unsubscribe();

}