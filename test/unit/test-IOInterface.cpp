#include <gtest/gtest.h>
#include "IO/IOInterface.h"

using namespace IO;

TEST(IOInterfaceTest, GenericInterfaceWrite)
{
    msg::real::TEST_MESSAGE_READ msg;
    msg.VAR1 = 10;
    msg.VAR2 = 25.0f;

    uint8_t buffer[32];
    GenericInterface interface;
    StaticQueue<uint8_t, BUFFER_SIZE>* queue = interface.getTXBuffer();
    memset(buffer, 0, sizeof(buffer));

    interface.writeMessage((uint8_t*)(&msg), msg.size);
    queue->dequeue(buffer, msg.size);

    EXPECT_EQ(((msg::real::TEST_MESSAGE_READ*)buffer)->VAR1, msg.VAR1);
    EXPECT_EQ(((msg::real::TEST_MESSAGE_READ*)buffer)->VAR2, msg.VAR2);

}