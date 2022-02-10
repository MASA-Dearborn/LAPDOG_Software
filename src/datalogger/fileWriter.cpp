#include "datalogger/fileWriter.h"
#include <stdio.h>

using namespace std;

FileWriter::FileWriter()
{

}

FileWriter::FileWriter(string name)
{
    index = 1;
    fileName = name;
    openFile();
}

void FileWriter::increment(int index)
{
    closeFile();
    index++;
}

int FileWriter::write(char* data, int size)
{
    file.write(data, size);
}

void FileWriter::openFile()
{
    char tempNameBuffer[128];
    sprintf(tempNameBuffer, "%s_%03d.log", fileName, index);

    file.open(tempNameBuffer, fstream::in | fstream::binary);
}

void FileWriter::closeFile()
{
    file.close();
}
