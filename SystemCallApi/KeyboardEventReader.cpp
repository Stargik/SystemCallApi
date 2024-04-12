#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <linux/input.h>

using namespace std;

struct KeyEvent {
    int code;
    string name;
};

struct ValueEvent {
    int value;
    string name;
};

vector<KeyEvent> key_events = {
    {1, "ESC"},
    {2, "1"},
    {3, "2"},
    {4, "3"},
    {5, "4"},
    {6, "5"},
    {7, "6"},
    {8, "7"},
    {9, "8"},
    {10,  "9"},
    {11,  "0"},
    {12, "-"},
    {13, "="},
    {14, "BACKSPACE"},
    {15, "TAB"},
    {16,  "Q"},
    {17,  "W"},
    {18,  "E"},
    {19,  "R"},
    {20,  "T"},
    {21,  "Y"},
    {22,  "U"},
    {23,  "I"},
    {24,  "O"},
    {25,  "P"},
    {26, "LEFTBRACE"},
    {27, "RIGHTBRACE"},
    {28, "ENTER"},
    {29, "LEFTCTRL"},
    {30,  "A"},
    {31,  "S"},
    {32,  "D"},
    {33,  "F"},
    {34,  "G"},
    {35,  "H"},
    {36,  "J"},
    {37,  "K"},
    {38,  "L"},
    {39, "SEMICOLON"},
    {40, "APOSTROPHE"},
    {41, "GRAVE"},
    {42, "LEFTSHIFT"},
    {43, "BACKSLASH"},
    {44, "Z"},
    {45, "X"},
    {46, "C"},
    {47, "V"},
    {48, "B"},
    {49, "N"},
    {50, "M"},
    {51, "COMMA"},
    {52, "DOT"},
    {53, "SLASH"},
    {54, "RIGHTSHIFT"},
    {55, "KPASTERISK"},
    {56, "LEFTALT"},
    {57, "SPACE"},
    {58, "CAPSLOCK"},
    {59, "F1"},
    {60, "F2"},
    {61, "F3"},
    {62, "F4"},
    {63, "F5"},
    {64, "F6"},
    {65, "F7"},
    {66, "F8"},
    {67, "F9"},
    {68, "F10"},
    {69, "NUMLOCK"}
};

vector<ValueEvent> value_events = {
    {0, "RELEASED"},
    {1, "PRESSED"},
    {2, "HELD"}
};

string get_key_name(int code) {
    for (const auto& key_event : key_events) {
        if (key_event.code == code) {
            return key_event.name;
        }
    }
    return "KEY_IS_NOT_RECOGNIZED";
}

string get_value_name(int value) {
    for (const auto& value_event : value_events) {
        if (value_event.value == value) {
            return value_event.name;
        }
    }
    return "VALUE_IS_NOT_RECOGNIZED";
}

int main(int argc, char *argv[]){
    string eventName = argv[1];
    string keyboard = "/dev/input/" + eventName; // Replace X with the event number of your keyboard
    ifstream keyboardInput(keyboard, ios::binary);

    struct input_event keyboardEvent;
    while (true) {
        keyboardInput.read(reinterpret_cast<char*>(&keyboardEvent), sizeof(struct input_event));
        if (keyboardEvent.type == EV_KEY && keyboardEvent.value >= 0 && keyboardEvent.value <= 2) {
            cout << "Event: " << keyboardEvent.value << " (" << get_value_name(keyboardEvent.value) << ")" << '\t';
            cout << "Code: " << keyboardEvent.code << " (" << get_key_name(keyboardEvent.code) << ")" << endl;
        }
    }
    keyboardInput.close();

    return 0;
}
