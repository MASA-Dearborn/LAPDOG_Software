#include "datalogger/dataLogger.h"
#include <ctime>
#include <sys/stat.h>

static char CREATE_LOGGER_NAME_BUFFER[512];
#define CREATE_LOGGER(file_location, interval, message_type)    strcpy(CREATE_LOGGER_NAME_BUFFER, file_location); \
                                                                strcat(CREATE_LOGGER_NAME_BUFFER, "/" #message_type); \
                                                                mkdir(CREATE_LOGGER_NAME_BUFFER, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); \
                                                                strcat(CREATE_LOGGER_NAME_BUFFER, "/" #message_type); \
                                                                loggers[msg::id::message_type] = { .log = new FileWriter(CREATE_LOGGER_NAME_BUFFER, interval), \
                                                                                                   .subscriber = createNewSubscriber(message_type) };

DataLogger::DataLogger()
{
    printf("Hello!\n");
    _createLogFolder();
    _init();
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
    printf("Log folder created\n");
}

void DataLogger::_init()
{
    CREATE_LOGGER(log_folder_name, 5000, TEST_MESSAGE)
}

void DataLogger::_createLogger()
{

}

void _data_logger_handler(union sigval data)
{

}