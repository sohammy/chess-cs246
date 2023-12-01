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

    Game myGame;

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << " -- Type 'play' to Get Started!" << endl;
    cout << " -- Type 'setup' to enter Setup Mode!" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;

    myGame.gameStart();
}