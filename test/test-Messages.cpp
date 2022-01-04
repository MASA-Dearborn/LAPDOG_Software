#include <gtest/gtest.h>
#include "messageTypes.h"

TEST(Messages, SetIdOnConstruct)
{

    msg::real::TEST_MESSAGE real;
    msg::raw::TEST_MESSAGE raw;
    
    EXPECT_EQ(real.id, msg::id::TEST_MESSAGE);
    EXPECT_EQ(raw.id, msg::id::TEST_MESSAGE);

}