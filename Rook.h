#pragma once
#include "Piece.h"

class Rook :public Piece {
public:
	//Constructor
	Rook(Color c);

	//Getter for symbol virtual function in piece class
	char getSymbol() const;

	// Rook moves in straight lines on same row or same coloumn
	bool isValidMove(int initialrow, int initialcol, int finalrow, int finalcol, Piece* const board[8][8]) const override;
};