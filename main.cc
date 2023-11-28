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

    Game myGame;

    if (input == "game") {

        string playerWhite = "";
        string playerBlack = "";

        cin >> playerWhite >> playerBlack;

        myGame.play(playerWhite, playerBlack);
    } 
    
    if (input == "setup") {
        myGame.setup();
    }
}

// THIS IS PART OF THE TEST!!