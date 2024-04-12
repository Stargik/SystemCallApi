#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#define MESSAGE_SIZE 256

using namespace std;

int main(int argc, char *argv[]){
    string pid = argv[1];
    string memFile = "/proc/" + pid + "/mem";
    uint64_t addr = stoull(argv[2], nullptr, 16);

    char mes[MESSAGE_SIZE];
    char mesNew[MESSAGE_SIZE];
    
    ifstream mem(memFile.c_str(), ios::in | ios::binary);
    mem.seekg((off_t)addr);
    mem.read(mes, MESSAGE_SIZE);
    mem.close();
    cout << "Message: " << mes << endl;
    while (true) {
        ifstream mem(memFile.c_str(), ios::in | ios::binary);
        mem.seekg((off_t)addr);
        mem.read(mesNew, MESSAGE_SIZE);
        mem.close();
        if (strcmp(mes, mesNew) != 0) {
            memset(mes, 0, MESSAGE_SIZE);
            strcpy(mes, mesNew);
            memset(mesNew, 0, MESSAGE_SIZE);
            cout << "Message: " << mes << endl;
        }
        sleep(1);
    }

    return 0;
}

