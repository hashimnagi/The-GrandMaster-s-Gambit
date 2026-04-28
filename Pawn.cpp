#include "Pawn.h"

Pawn::Pawn(Color c) :Piece(c, PiecesType::PAWN) {};

//Getter for symbol virtual function in piece class
char Pawn::getSymbol() const {
	if (color == Color::WHITE)
		return'P';
	else
		return 'p';
}

// Pawn is the most basic piece, it can move straight 2 in first move then straight 1 in rest but kill diagonal only in 1 forward direction
bool Pawn::isValidMove(int initialrow, int initialcol, int finalrow, int finalcol, Piece* const board[8][8]) const {

	//White moves up so row decreases and black moves down so row decreases
	int direction;
	if (color == Color::WHITE)
		direction = -1;
	else
		direction = 1;

	int rowdifference = finalrow - initialrow;
	int coldifference = finalcol - initialcol;
	// 3 cases of pawn movement
	//case 1 moving in straight forward direaction
	int startrow;
	if (coldifference == 0 && rowdifference == direction) {
		bool ok;
		// if forward box is empty
		if (board[finalrow][finalcol] == nullptr)
			ok = true;
		else
			ok = false;

		return ok;
	}
	//case 2 move 2 sqaures if first turn and check that forward destination box is empty
	if (color == Color::WHITE) {
		// starting row for white
		startrow = 6;
	}
	else
		//starting row for black
		startrow = 1;
	// conditions for double square movement
	if (coldifference == 0 && rowdifference == 2 * direction && initialrow == startrow) {
		//middle row is where the pawn will move if it moves 2 units
		int middle = initialrow + direction;
		bool ok;
		//check if middlerow is empty or not
		if (board[middle][initialcol] == nullptr && board[finalrow][finalcol] == nullptr)
			ok = true;
		else
			ok = false;

		return ok;
}
	// case 3 attacking diagonally 
	if (abs(coldifference) == 1 and rowdifference == direction) {
		//Store address of destination in a pointer
		//check if diagonal piece is of same color or not
		Piece* destination = board[finalrow][finalcol];
		if (destination != nullptr && destination->getColor() == this->getColor())
			return false;
	}

	return false;
}
