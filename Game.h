// Game.h

#pragma once

// standard library first, alphabetical order
#include <iostream>
#include <string>

// then your own headers, alphabetical order
#include "Board.h"
#include "FileManager.h"
#include "Player.h"
#include "Renderer.h"
#include "Types.h"
using namespace std;

class Game {
    private:
    Board       board;
    Player      player1;
    Player      player2;
    Player *currentPlayer;
    bool        gameOver;
    GameRecords  record;
    FileManager fileManager;

    bool parseInput(const string &input , int &row , int &col) const;
    bool isInCheck(Color color) const;
    bool wouldLeaveKingInCheck(int fr , int fc , int tr , int tc , Color color) const;
    bool hasLegalMoves(Color color) const;
    void switchTurn( );
    int getValidMoves(int row , int col , int resultRows[ ] , int resultCols[ ]) const;
    public:
    void startGUI( );
    Game(string name1 , string name2);
    void start( );
    void playTurn( );
};