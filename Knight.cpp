#include "Knight.h"

	//Constructor
Knight::Knight(Color c) :Piece(c, PiecesType::KNIGHT) {};

//Getter for symbol virtual function in piece class
char Knight::getSymbol() const {
	if (color == Color::WHITE)
		return 'K';
	else
		return 'k';
}
// Kight moves in L shape and may move and jump over other other pieces
bool Knight::isValidMove(int initialrow, int initialcol, int finalrow, int finalcol, Piece* const board[8][8])const {
		int rowdifference = abs(finalrow - initialrow);
		int coldifference = abs(finalcol - initialcol);

	  // For L shape jump difference between rowdifference and col difference must be 1
		bool Lshape;
		if ((rowdifference == 2 && coldifference == 1) || (rowdifference == 1 && coldifference == 2))
			Lshape = true;
		else
			Lshape = false;

		if (!Lshape)
			return false;
	// No need to check the path logic as it jumps over other pieces

	// now we check our destination square
	//we store the destination address in a pointer
		Piece* destination = board[finalrow][finalcol];
	// if destination has the same color piece then also invalid
		if (destination != nullptr && destination->getColor() == this->getColor())
			return false;

	return true;

}