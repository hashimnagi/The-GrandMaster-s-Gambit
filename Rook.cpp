#include "Rook.h"

//Constructor
Rook::Rook(Color c) : Piece(c, PiecesType::ROOK) {};

//Getter for symbol virtual function in piece class
char Rook::getSymbol() const {
	if (color == Color::WHITE)
		return 'R';
	else
		return 'r';
}


// Rook moves in straight lines on same row or same coloumn
bool Rook::isValidMove(int initialrow, int initialcol, int finalrow, int finalcol, Piece* const board[8][8])const {
	if (initialrow != finalrow && initialcol != finalcol)
		return false;
	// for horizontal movement rowStep=0
	// for vertical movement colStep=0

	int rowStep=0, colStep=0;
	if (finalrow > initialrow)
		rowStep = 1;
	else
		rowStep = -1;
	if (finalcol > initialcol)
		colStep = 1;
	else
		colStep = -1;

	int checkRow = initialrow + rowStep;
	int checkCol = initialcol + colStep;

	//now we check if something is blocking our path or not using a loop

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