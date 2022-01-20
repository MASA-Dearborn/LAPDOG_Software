#include <fstream>
#include <string>

using namespace std;

class FileWriter {
    public:
        FileWriter();
        FileWriter(string name); // index defaults to 0
        
        void increment(int index);
        int write(char* data, int size);
        
    protected:

        void openFile();
        void closeFile();

        fstream file;
        string fileName;
        int index;
}