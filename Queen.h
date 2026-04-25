#pragma once
#include "Piece.h"


class Queen :public Piece {
public:
	//Constructor
	Queen(Color c);

	//Getter for symbol virtual function in piece class
	char getSymbol() const;

	// Queen moves in all 8 directions any number of squares
	bool isValidMove(int initialrow, int initialcol, int finalrow, int finalcol, Piece* const board[8][8]) override;
};
