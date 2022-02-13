#include "datalogger/fileWriter.h"
#include <stdio.h>

using namespace std;

FileWriter::FileWriter()
{

}

FileWriter::FileWriter(const char* name, uint64_t file_length_ms);
{
    file_index = 0;
    strcpy(file_name, name)
    _createNewIncrementedFile();
}

int FileWriter::write(void* data, int size)
{
    file.write(data, size);
}

void FileWriter::_createNewIncrementedFile()
{
    closeFile();
    index++;
    openFile();
}

void FileWriter::_openFile()
{
    static char indexedFileNameBuffer[128];
    sprintf(tempNameBuffer, "%s_%04d.log", fileName, index);
    file.open(tempNameBuffer, fstream::in | fstream::binary);
}

void FileWriter::_closeFile()
{
    if (file.is_open())
        file.close();
}

bool FileWriter::_hasTimeIntervalPassed()
{

}