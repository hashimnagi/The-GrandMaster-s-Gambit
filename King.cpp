#include "King.h"
#include<cmath>


King::King(Color c):Piece(c,PiecesType::KING) {
};

// Capital K is considered for player 1 and small k for player 2
char King::getSymbol() const {
	if (color == Color::WHITE)
		return 'K';
	else
		return 'k';
}


//King only moves 1 step in all the directions
bool King::isValidMove(int initialrow, int initialcol, int finalrow, int finalcol, Piece* const board[8][8])const {

	//First we calculate how far is king trying to go
	int rowdifference = abs(finalrow - initialrow);
	int coldifference = abs(finalcol - initialcol);

	// now check conditions for invalid move
	// If he moved more than 1 block or didnt move at all then invalid
	if ((rowdifference == 0 && coldifference == 0) || (rowdifference > 1 || coldifference > 1))
		return false;

	// now we check our destination square
	//we store the destination address in a pointer
	Piece* destination = board[finalrow][finalcol];
	// if destination has the same color piece then also invalid
	if (destination != nullptr && destination->getColor() == this->getColor())
		return false;

	//after checking all invalid conditions we return isValid as true
	return true;

}
