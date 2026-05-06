// main.cpp
#include "Game.h"
#include <iostream>
#include<string>
using namespace std;

int main( ) {
    string name1 , name2;

    cout << "Enter White player's name: ";
    getline(cin,name1);
    cout << "Enter Black player's name: ";
    getline(cin,name2);

    Game chess(name1 , name2);
    chess.startGUI( );

    system("pause");
    return 0;
}
