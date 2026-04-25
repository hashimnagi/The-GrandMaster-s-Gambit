#pragma once
#include "Piece.h"

class Bishop :public Piece {
public:
public:
	//Constructor
	Bishop(Color c);

	//Getter for symbol virtual function in piece class
	char getSymbol() const;

	// Bishop moves in diagonal lines only
	bool isValidMove(int initialrow, int initialcol, int finalrow, int finalcol, Piece* const board[8][8]) const override;

};