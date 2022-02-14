#include "datalogger/dataLogger.h"

#include <ctime>
#include <filesystem>
#include <sys/stat.h>

DataLogger::DataLogger()
{
    _createLogFolder();
}

DataLogger::~DataLogger()
{

}

void DataLogger::_createLogFolder()
{
    std::time_t current_time = std::time(NULL);
    std::tm* broken_time = std::localtime(&current_time);
    sprintf(log_folder_name, "log-%02d:%02d:%02d", broken_time->tm_hour, broken_time->tm_min, broken_time->tm_sec);
    mkdir(log_folder_name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

void DataLogger::_initFileWriters()
{

}

void _data_logger_handler(union sigval data)
{

}