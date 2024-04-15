#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

#define MESSAGE_SIZE 256

using namespace std;

int main() {
    char* message = nullptr;
    message = (char*)malloc(MESSAGE_SIZE);
    while (true) {
        cout << "Message: ";
        string word;
        std::getline(std::cin, word);

        if (word == "stop") {
            break;
        }
        memset(message, 0, MESSAGE_SIZE);
        strcpy(message, word.c_str());
        cout << "Active message: " << message << endl;
        cout << "PID: " << getpid() << endl;
        cout << "Address: " << (void *)message << endl;
    }
    free(message);

    return 0;
}


