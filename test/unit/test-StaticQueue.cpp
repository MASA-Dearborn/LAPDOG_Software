#include <gtest/gtest.h>
#include <cstring>

#define protected public
#include "StaticQueue.h"
#undef protected


TEST(StaticQueueTest, Initialization) 
{
    StaticQueue<uint8_t, 16> buffer;
    EXPECT_EQ(buffer.getBufferSize(), 16);
    EXPECT_EQ(buffer.top, nullptr);
    EXPECT_EQ(buffer.bottom, nullptr);
}

TEST(StaticQueueTest, EnqueueMultiple)
{

    StaticQueue<uint8_t, 8> buffer;
    uint8_t data[4] = {1, 2, 3, 4};
    const int size = 4;

    EXPECT_EQ(buffer.enqueue(data, size), 4);
    EXPECT_TRUE(0 == std::memcmp(data, buffer.data, size));

}

TEST(StaticQueueTest, EnqueueMultipleWrap)
{

    StaticQueue<uint8_t, 4> buffer;
    buffer.top = buffer.data + 2;
    buffer.bottom = buffer.data + 2;

    uint8_t data[4] = {1, 2, 3, 4};
    uint8_t expect[4] = {3, 4, 1, 2};
    const int size = 4;

    EXPECT_EQ(buffer.enqueue(data, size), 4);
    EXPECT_TRUE(0 == std::memcmp(expect, buffer.data, size));

}

TEST(StaticQueueTest, EnqueueMultipleOverflow)
{
    StaticQueue<uint8_t, 4> buffer;

    uint8_t data[5] = {1, 2, 3, 4, 5};

    EXPECT_EQ(buffer.enqueue(data, 5), 0);

}

TEST(StaticQueueTest, DequeueMultiple)
{
    StaticQueue<uint8_t, 8> buffer;

    uint8_t data[4] = {1, 2, 3, 4};
    uint8_t dest[4];
    buffer.enqueue(data, 4);

    EXPECT_EQ(buffer.dequeue(dest, 4), 4);
    EXPECT_TRUE(0 == std::memcmp(data, buffer.data, 4));
}

TEST(StaticQueueTest, DequeueMultipleUnderflow)
{
    StaticQueue<uint8_t, 8> buffer;
    
    uint8_t data[4] = {1, 2, 3, 4};
    uint8_t dest[10];
    buffer.enqueue(data, 4);

    EXPECT_EQ(buffer.dequeue(dest, 6), 0);
    EXPECT_EQ(buffer.dequeue(dest, 10), 0);

}

TEST(StaticQueueTest, DequeueMultipleWrap)
{

    StaticQueue<uint8_t, 6> buffer;
    buffer.top = buffer.data + 4;
    buffer.bottom = buffer.data + 4;

    uint8_t data[4] = {1, 2, 3, 4};
    uint8_t dest[4];
    const int size = 4;

    buffer.enqueue(data, size);
    buffer.dequeue(dest, size);
    EXPECT_TRUE(0 == std::memcmp(data, dest, size));

}

TEST(StaticQueueTest, DequeueBeforeEnqueue)
{
    StaticQueue<uint8_t, 8> buffer;
    uint8_t dest[8];

    EXPECT_EQ(buffer.dequeue(dest, 4), 0);

}

TEST(StaticQueueTest, EnqueueAndDequeueFromBound)
{
    StaticQueue<uint8_t, 4> buffer;
    uint8_t data[4] = {0x01, 0x02, 0x03, 0x04};
    uint8_t dest[2];

    buffer.enqueue(data, 2);
    buffer.dequeue(dest, 2);
    buffer.enqueue(data + 2, 2);
    EXPECT_TRUE(buffer.top == buffer.data);

    buffer.dequeue(dest, 2);
    EXPECT_TRUE(0 == std::memcmp(data + 2, dest, 2));
    EXPECT_TRUE(buffer.bottom == buffer.data);
}