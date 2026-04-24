#pragma once
#include "Piece.h"

class King :public Piece {
public:
	//Constructor
	King(Color c);

	//Getter for symbol virtual function in piece class
	char getSymbol() const;

	//King only moves 1 step in all the directions
	bool isValidMove(int initialrow, int initialcol, int finalrow, int finalcol, Piece* const board[8][8]);

};