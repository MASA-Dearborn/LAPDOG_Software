#include <gtest/gtest.h>
#include <cstring>

#define protected public
#include "StaticQueue.h"
#undef protected


TEST(StaticQueueTest, Initialization) 
{
    StaticQueue<int, 16> buffer;
    EXPECT_EQ(buffer.getBufferSize(), 16);
    EXPECT_EQ(buffer.top, 0);
    EXPECT_EQ(buffer.bottom, 0);
}

TEST(StaticQueueTest, EnqueueMultiple)
{

    StaticQueue<int, 8> buffer;
    int data[4] = {1, 2, 3, 4};
    const int size = 4;

    EXPECT_EQ(buffer.enqueue(data, size), 4);
    EXPECT_TRUE(0 == std::memcmp(data, buffer.data, size));

}

TEST(StaticQueueTest, EnqueueMultipleWrap)
{

    StaticQueue<int, 4> buffer;
    buffer.top = 2;
    buffer.bottom = 2;

    int data[4] = {1, 2, 3, 4};
    int expect[4] = {3, 4, 1, 2};
    const int size = 4;

    EXPECT_EQ(buffer.enqueue(data, size), 4);
    EXPECT_TRUE(0 == std::memcmp(expect, buffer.data, size));

}

TEST(StaticQueueTest, EnqueueMultipleOverflow)
{
    StaticQueue<int, 4> buffer;

    int data[5] = {1, 2, 3, 4, 5};

    EXPECT_EQ(buffer.enqueue(data, 5), 0);

}

TEST(StaticQueueTest, DequeueMultiple)
{
    StaticQueue<int, 8> buffer;

    int data[4] = {1, 2, 3, 4};
    int dest[4];
    buffer.enqueue(data, 4);

    EXPECT_EQ(buffer.dequeue(dest, 4), 4);
    EXPECT_TRUE(0 == std::memcmp(data, buffer.data, 4));
}

TEST(StaticQueueTest, DequeueMultipleUnderflow)
{
    StaticQueue<int, 8> buffer;
    
    int data[4] = {1, 2, 3, 4};
    int dest[10];
    buffer.enqueue(data, 4);

    EXPECT_EQ(buffer.dequeue(dest, 6), 0);
    EXPECT_EQ(buffer.dequeue(dest, 10), 0);

}

TEST(StaticQueueTest, DequeueMultipleWrap)
{

    StaticQueue<int, 6> buffer;
    buffer.top = 4;
    buffer.bottom = 4;

    int data[4] = {1, 2, 3, 4};
    int dest[4];
    const int size = 4;

    buffer.enqueue(data, size);
    buffer.dequeue(dest, size);
    EXPECT_TRUE(0 == std::memcmp(data, dest, size));

}

TEST(StaticQueueTest, DequeueBeforeEnqueue)
{
    StaticQueue<int, 8> buffer;
    int dest[8];

    EXPECT_EQ(buffer.dequeue(dest, 4), 0);

}