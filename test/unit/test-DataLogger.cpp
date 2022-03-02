#include <gtest/gtest.h>
#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include "datalogger/dataLogger.h"
#include "broker/broker.h"

void delete_file(const char* path)
{
    char full_path[300];
    DIR* directory = opendir(path);
    int retval = 0;

    dirent* entry;
    while ((entry = readdir(directory)) != NULL)
    {

        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
             continue;

        switch (entry->d_type)
        {
        case DT_DIR:
            sprintf(full_path, "%s/%s", path, entry->d_name);
            delete_file(full_path);
            break;
        case DT_REG:
            sprintf(full_path, "%s/%s", path, entry->d_name);
            retval = unlink(full_path);
            if (retval < 0) perror("unlink");
            break;
        }
    }

    retval = rmdir(path);
    if (retval < 0) perror("unlink");

}

class DataLoggerFixture : public ::testing::Test
{
public:
    void SetUp()
    {
        dl = new DataLogger();
    }

    void TearDown()
    {
        delete_file(dl->log_folder_name);
        delete dl;
    }

    DataLogger* dl;

};

TEST_F(DataLoggerFixture, TestDataLoggerWrite)
{
    char file_path[1024];
    char data_read[64] = {0};
    char data_expected[64] = {0};
    int retval = 0;

    strcpy(file_path, dl->getLogFolderNamePtr());
    strcat(file_path, "/TEST_MESSAGE/TEST_MESSAGE_0001.log");

    // Send a message for logging
    pubsub::Publisher<msg::real::TEST_MESSAGE>* pub = createNewPublisher(TEST_MESSAGE);
    msg::real::TEST_MESSAGE send_message;
    send_message.test = 5;
    send_message.VAR2 = 0;
    pub->publish(&send_message);

    // Wait so datalogger timer can trigger (50ms)
    usleep(100000);
    dl->getLoggerPtr(msg::id::TEST_MESSAGE)->log->closeFile();
    msg::conv::stringifyRealMessage(data_expected, &send_message);

    // Open the file written to
    int file_descriptor = open(file_path, O_RDWR);
    EXPECT_TRUE(file_descriptor > 0);
 
    retval = read(file_descriptor, data_read, 64);
    EXPECT_STREQ(data_read, data_expected) << data_read << " != " << data_expected << "\n";

}