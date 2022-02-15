#include <string>
#include <chrono>

class FileWriter {
    public:
        FileWriter();
        FileWriter(const char* name, uint64_t file_length_ms);
        ~FileWriter();
        
        int writeToFile(void* data, int size);
        void setBaseName(const char* name);
        void setIntervalMilliseconds(uint64_t file_length_ms);
        void openFile();
        void closeFile();

    protected:
        /* File Interaction Methods */
        void _createNewIncrementedFile();

        /* Time Interaction Methods */
        bool _hasTimeIntervalPassed();

        /* Time Member Variables */
        std::chrono::time_point<std::chrono::steady_clock> time_since_first_write;
        uint64_t file_length_ms;
        bool opened_file_written = false;

        /* File Member Variables */
        int file_descriptor = -1;
        char file_name[128] = {0};
        int file_index = 0;
};