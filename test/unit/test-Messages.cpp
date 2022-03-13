#include <gtest/gtest.h>
#include "messageTypes.h"

TEST(Messages, SetIdOnConstruct)
{

    msg::real::TEST_MESSAGE_READ real;
    msg::raw::TEST_MESSAGE_READ raw;
    
    EXPECT_EQ(real.id, msg::id::TEST_MESSAGE_READ);
    EXPECT_EQ(raw.id, msg::id::TEST_MESSAGE_READ);

}