#include "datalogger/fileWriter.h"
#include "broker/broker.h"
#include "timer.h"

struct Logger
{
    FileWriter* log;
    pubsub::GenericSubscriber* subscriber;
};

struct data_logger_timer_data
{

};

void _data_logger_handler(union sigval data);

class DataLogger 
{
    public:
        DataLogger();
        ~DataLogger();

    private:
        void _createLogFolder();
        void _createLogger();
        void _init();

        /* IO Handling Data */
        Timer io_timer;
        data_logger_timer_data io_event_data;

        char log_folder_name[256];
        std::array<Logger, msg::id::META_NUM_MESSAGES> loggers;

};
