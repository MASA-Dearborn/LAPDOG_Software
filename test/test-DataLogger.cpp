#include <gtest/gtest.h>
#include <stdio.h>
#include <dirent.h>
#include "datalogger/dataLogger.h"

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

TEST_F(DataLoggerFixture, temp)
{
    printf("Hello\n");
}