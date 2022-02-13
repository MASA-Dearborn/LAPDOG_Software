#include <fstream>
#include <string>
#include <chrono>

class FileWriter {
    public:
        FileWriter();
        FileWriter(const char* name, uint64_t file_length_ms);
        ~FileWriter();
        
        int write(void* data, int size);
        
    protected:
        /* File Interaction Methods */
        void _createNewIncrementedFile();
        void _openFile();
        void _closeFile();

        /* Time Interaction Methods */
        bool _hasTimeIntervalPassed();

        /* Time Member Variables */
        std::chrono::time_point<std::chrono::steady_clock> time_since_first_write;
        uint64_t file_length_ms;
        bool opened_file_written = false;

        /* File Member Variables */
        std::fstream file_obj;
        char file_name[128] = {0};
        int file_index = 0;
};