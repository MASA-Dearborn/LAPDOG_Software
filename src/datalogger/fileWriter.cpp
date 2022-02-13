#include "datalogger/fileWriter.h"
#include <string.h>
#include <stdio.h>

using namespace std;

FileWriter::FileWriter()
{

}

FileWriter::FileWriter(const char* name, uint64_t file_length_ms)
{
    file_index = 0;
    strcpy(file_name, name);
    _createNewIncrementedFile();
}

int FileWriter::write(void* data, int size)
{
    file_obj.write((const char*)data, size);
    return size;
}

void FileWriter::_createNewIncrementedFile()
{
    _closeFile();
    file_index++;
    _openFile();
}

void FileWriter::_openFile()
{
    static char indexedFileNameBuffer[144];
    sprintf(indexedFileNameBuffer, "%s_%04d.log", file_name, file_index);
    file_obj.open(indexedFileNameBuffer, fstream::in | fstream::binary);
}

void FileWriter::_closeFile()
{
    if (file_obj.is_open())
        file_obj.close();
}

bool FileWriter::_hasTimeIntervalPassed()
{
    // TODO: implement
    return false;
}