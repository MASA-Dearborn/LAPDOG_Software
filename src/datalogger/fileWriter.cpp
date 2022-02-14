#include "datalogger/fileWriter.h"
#include <string.h>
#include <stdio.h>

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
    
}

int FileWriter::write(void* data, int size)
{
    file_obj.write((const char*)data, size);
    return size;
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
    file_obj.open(indexedFileNameBuffer, fstream::in | fstream::binary);
}

void FileWriter::closeFile()
{
    if (file_obj.is_open())
        file_obj.close();
}

bool FileWriter::_hasTimeIntervalPassed()
{
    // TODO: implement
    return false;
}