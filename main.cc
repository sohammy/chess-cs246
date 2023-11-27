#include <iostream>
#include <string>
#include <unistd.h>

#include "game.h"

using namespace std;

int main() {
    string input;

    cout << "Welcome to Chess!" << endl;
    cout << "By Hudson, Soham, and Krish" << endl;
    cout << endl;

    for (unsigned i = 0; i < input.size(); ++i) {
        input[i] = tolower(input[i]);
    }

    if (input == "game") {
        cout << "Starting Game" << endl;
        sleep(1);
        Game myGame;

        myGame.play();
    } 
    
    if (input == "setup") {
        cout << "Entering Setup Mode..." << endl;
        sleep(1);
        cout << endl;
        cout << "You are in Setup Mode, type 'done' to leave" << endl;
        cout << "What piece would you like to add?" << endl;

        while (cin) {
            cout << "What piece would you like to add?" << endl;
            // Enter Setup Instructions
        }
    }
}