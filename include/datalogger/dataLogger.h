#include "datalogger/fileWriter.h"
#include "broker/broker.h"
#include "timer.h"

#define LOGGER_INTERVAL_BASE_MS 10

class DataLogger;

struct Logger
{
    Logger() { log = nullptr; subscriber == nullptr; }
    FileWriter* log;
    pubsub::GenericSubscriber* subscriber;
};

struct data_logger_timer_data
{
    DataLogger* obj;
};

void _data_logger_handler(union sigval data);

class DataLogger 
{
    public:
        DataLogger();
        ~DataLogger();

        void addLoggableMessage(msg::id::MessageType id, uint64_t interval);
        const char* getLogFolderNamePtr() { return log_folder_name; }
        const Logger* getLoggerPtr(msg::id::MessageType id) { return &loggers[id]; }

    protected:
        friend void _data_logger_handler(union sigval data);
        friend class DataLoggerFixture;
        void _createLogFolder();

        /* IO Handling Data */
        Timer io_timer;
        data_logger_timer_data io_event_data;

        uint64_t time_epoch_ms_at_start;
        char log_folder_name[256];
        std::array<Logger, msg::id::META_NUM_MESSAGES> loggers;

};
