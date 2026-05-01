// main.cpp
#include "Game.h"
#include <iostream>
using namespace std;

int main( ) {
    string name1 , name2;

    cout << "Enter White player's name: ";
    cin >> name1;
    cout << "Enter Black player's name: ";
    cin >> name2;

    Game chess(name1 , name2);
    chess.startGUI( );

    return 0;
}