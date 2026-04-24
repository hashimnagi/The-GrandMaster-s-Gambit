#include "Queen.h"
#include<cmath>

//Constructor
	Queen::Queen(Color c) : Piece(c, PiecesType::QUEEN) {};

//uppercase letters are for player white and lowecase are for player black
	char Queen::getSymbol() const {
		if (color == Color::WHITE)
			return'Q';
		else
			return 'q';
	}

	// Queen moves in all 8 directions any number of squares

	bool Queen::isValidMove(int initialrow, int initialcol, int finalrow, int finalcol, Piece* const board[8][8])const {

		int rowdifference = abs(finalrow - initialrow);
		int coldifference = abs(finalcol - initialcol);

		//Queen can only move in same row or same col or diagonally

		bool Straight = (initialrow == finalrow || initialcol == finalcol);
		bool Diagonal = (rowdifference == coldifference);

		if (!Straight && !Diagonal)
			return false;

		// Now for the movement of the Queen
		// We take horizontal movement as rowsteps = 0
		// We take vertical movement as colsteps = 0
		// We take diagonal movement as bot either 1 or -1
		int rowStep;
		if (finalrow > initialrow) {
			rowStep = 1;
		}
		else if (finalrow < initialrow) {
			rowStep = -1;
		}
		else
			rowStep = 0;

		int colStep;

		if (finalcol > initialcol) {
			colStep = 1;
		}
		else if (finalcol < initialcol) {
			colStep = -1;
		}
		else
			colStep = 0;

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
