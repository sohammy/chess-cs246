#include "game.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    string input;

    cout << "Chess." << endl;
    cout << "By Hudson, Soham, & Krish" << endl;
    cout << endl;

    cin >> input;

    for (unsigned i = 0; i < input.size(); ++i) {
        input[i] = tolower(input[i]); // takes all input and makes it lowercase
    }

    if (input == "game") {

        string playerWhite = "";
        string playerBlack = "";

        cin >> playerWhite >> playerBlack;

        Game myGame;
        myGame.play(playerWhite, playerBlack);
    } 
    
    if (input == "setup") {
        cout << "Entering Setup Mode..." << endl;
        cout << endl;
        cout << "You are in Setup Mode, type 'done' to leave" << endl;
        cout << "What piece would you like to add?" << endl;

        while (cin >> input) {

            if (input == "done") {
                break;
            }

            // Enter Setup Instructions

            cout << "What piece would you like to add?" << endl;
        }
    }
}

// THIS IS PART OF THE TEST!!