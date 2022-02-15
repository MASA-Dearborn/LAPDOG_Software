#include "datalogger/fileWriter.h"
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

FileWriter::FileWriter()
{
    file_index = 1;
}

FileWriter::FileWriter(const char* name, uint64_t file_length_ms)
{
    file_index = 0;
    setBaseName(name);
    setIntervalMilliseconds(file_length_ms);
    _createNewIncrementedFile();
}

FileWriter::~FileWriter()
{
    closeFile();
}

int FileWriter::writeToFile(void* data, int size)
{
    return write(file_descriptor, data, size);
}

void FileWriter::setBaseName(const char* name)
{
    strcpy(file_name, name);
}

void FileWriter::setIntervalMilliseconds(uint64_t file_length_ms)
{
    this->file_length_ms = file_length_ms;
}


void FileWriter::_createNewIncrementedFile()
{
    closeFile();
    file_index++;
    openFile();
}

void FileWriter::openFile()
{
    static char indexedFileNameBuffer[144];
    sprintf(indexedFileNameBuffer, "%s_%04d.log", file_name, file_index);
    printf("Opening: %s\n", indexedFileNameBuffer);
    file_descriptor = open(indexedFileNameBuffer, O_RDWR | O_CREAT);
    if (file_descriptor < 0)
        perror("Open");
}

void FileWriter::closeFile()
{
    if (file_descriptor > 0)
    {
        close(file_descriptor);
        file_descriptor = -1;
    }
}

bool FileWriter::_hasTimeIntervalPassed()
{
    // TODO: implement
    return false;
}