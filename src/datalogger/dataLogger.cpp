#include "datalogger/dataLogger.h"
#include "messageTypes.h"

#include <ctime>
#include <sys/stat.h>
#include <chrono>

DataLogger::DataLogger()
{
    /* Setup Base Time*/
    using namespace std::chrono;
    time_epoch_ms_at_start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    /* Setup Object */
    _createLogFolder();

    /* Setup the Timer */
    io_event_data.obj = this;
    io_timer.setHandler((void (*)(union sigval))&_data_logger_handler);
    io_timer.setHandlerDataPointer(&io_event_data);
    io_timer.setIntervalMilliseconds(LOGGER_INTERVAL_BASE_MS);
    io_timer.setStartDelayMilliseconds(LOGGER_INTERVAL_BASE_MS);
    io_timer.startTimer();
}

DataLogger::~DataLogger()
{
    for (Logger& logger : loggers)
    {
        if (logger.log != nullptr)
            logger.log->closeFile();
    }
}

void DataLogger::addLoggableMessage(msg::id::MessageType id, uint64_t interval)
{
    char buffer[256];

    // create message folder
    strcpy(buffer, log_folder_name);
    strcat(buffer, "/");
    strcat(buffer, msg::messageNames[id]);
    mkdir(buffer, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    
    // create message log file base name
    strcat(buffer, "/");
    strcat(buffer, msg::messageNames[id]);

    // Add to logger
    loggers[id].log = new FileWriter(buffer, interval, time_epoch_ms_at_start); \
    loggers[id].subscriber = pubsub::generateSubscriber(id);
}

void DataLogger::_createLogFolder()
{
    std::time_t current_time = std::time(NULL);
    std::tm* broken_time = std::localtime(&current_time);
    sprintf(log_folder_name, "log_%02d_%02d_%02d", broken_time->tm_hour, broken_time->tm_min, broken_time->tm_sec);
    mkdir(log_folder_name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

void _data_logger_handler(union sigval data)
{
    static char string_buffer[1024];
    data_logger_timer_data* args = (data_logger_timer_data*)data.sival_ptr;
    DataLogger* obj = args->obj;

    for(Logger& logger : obj->loggers)
    {
        if (logger.log == nullptr || logger.subscriber == nullptr)
            continue;

        if (logger.subscriber->isDataAvailable()) {
            msg::conv::stringifyRealMessage(string_buffer, logger.subscriber->getGenericPointer());
            logger.subscriber->clearDataAvailable();
            logger.log->writeToFile(string_buffer, strlen(string_buffer));
        }
    }
}