#include "Bishop.h"
#include<cmath>

//Constructor
Bishop::Bishop(Color c) : Piece(c, PiecesType::BISHOP) {};

//Getter for symbol virtual function in piece class
char Bishop:: getSymbol() const {
	if (color == Color::WHITE)
		return 'B';
	else
		return 'b';
}

// Bishop moves in diagonal lines only
bool Bishop::isValidMove(int initialrow, int initialcol, int finalrow, int finalcol, Piece* const board[8][8]) const {
	// for diagonals the row difference must be equal to coloumns difference
	int rowdifference = abs(finalrow - initialrow);
	int coldifference = abs(finalcol - initialcol);

	if (rowdifference != coldifference)
		return false;
	// for diagonal rowstep and colstep must be either 1, -1
	int rowStep;
	int colStep;

	if (finalrow > initialrow)
		rowStep = 1;
	else
		rowStep = -1;
	if (finalcol > initialcol)
		colStep = 1;
	else
		colStep = -1;

	//now we check if something is blocking our path or not using a loop
	int checkRow = initialrow + rowStep;
	int checkCol = initialcol + colStep;

	while (checkRow != finalrow || checkCol != finalcol) {
		if (board[checkRow][checkCol] != nullptr)
			return false;

		//now move to next step
		checkRow += rowStep;
		checkCol += colStep;
	}
	// now we check our destination square
	//we store the destination address in a pointer
	Piece* destination = board[finalrow][finalcol];
	// if destination has the same color piece then also invalid
	if (destination != nullptr && destination->getColor() == this->getColor())
		return false;

	return true;

}