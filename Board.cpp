#include"Board.h"
#include<iostream>

using namespace std;

Board::Board( ) {
	for ( int i = 0; i < 8; i++ ) {
		for ( int j = 0; j < 8; j++ ) {
			grid [ i ][ j ] = nullptr;
		}
	}
}

void Board::intiailize( ) {
	//Black pieces ka setup
	grid [ 0 ][ 0 ] = new Rook(Color::BLACK);
	grid [ 0 ][ 1 ] = new Knight(Color::BLACK);
	grid [ 0 ][ 2 ] = new Bishop(Color::BLACK);
	grid [ 0 ][ 3 ] = new Queen(Color::BLACK);
	grid [ 0 ][ 4 ] = new King(Color::BLACK);
	grid [ 0 ][ 5 ] = new Bishop(Color::BLACK);  
	grid [ 0 ][ 6 ] = new Knight(Color::BLACK);  
	grid [ 0 ][ 7 ] = new Rook(Color::BLACK);
	for ( int i = 0; i < 8; i++ ) {
		grid [ 1 ][ i ] = new Pawn(Color::BLACK);
	}
	
	//White pieces are setup on the board
	grid [ 7 ][ 0 ] = new Rook(Color::WHITE);
	grid [ 7 ][ 1 ] = new Knight(Color::WHITE);
	grid [ 7 ][ 2 ] = new Bishop(Color::WHITE);
	grid [ 7 ][ 3 ] = new Queen(Color::WHITE);
	grid [ 7 ][ 4 ] = new King(Color::WHITE);
	grid [ 7 ][ 5 ] = new Bishop(Color::WHITE);
	grid [ 7 ][ 6 ] = new Knight(Color::WHITE);
	grid [ 7 ][ 7 ] = new Rook(Color::WHITE);

	for ( int i = 0; i < 8; i++) {
		grid [ 6 ][ i ] = new Pawn(Color::WHITE);
	} 
}

//for making pieces on their own positioin

Piece* Board::getPiece(int row , int col)const {
	if ( !isInBounds(row , col) ) {
		return nullptr;
	}
	return grid [ row ][ col ];
}

//for placing the pieces on their own position
void Board::setPiece(int row , int col , Piece *piece) {
	if ( isInBounds (row , col ) ) {
		grid [ row ][ col ] = piece;
	}
}

//for moving pieces from one square to another
Piece *Board::movePiece(int fromtheRow , int fromtheCol , int totheRow , int totheCol) {
	Piece *captured = grid [ totheRow ][ totheCol ];
	grid [ totheRow ][ totheCol ] = grid [ fromtheRow ][ fromtheCol ];
	grid [ fromtheRow ][ fromtheCol ] = nullptr;

	return captured;
}

bool Board::isInBounds(int row , int col)const {
	const int SIZE = 8;
	bool check =  ( row >= 0 && col >= 0 ) && ( row < SIZE && col < SIZE );

	return check;
}

bool Board::findKing(Color color , int &row , int &col)const {
	for ( int i = 0; i < 8; i++ ) {
		for ( int j = 0; j < 8; j++ ) {
			if ( grid [ i ][ j ] != nullptr &&
			   grid [ i ][ j ]->getType( ) == PiecesType::KING &&
			   grid [ i ][ j ]->getColor( ) == color ) {
				row = i;
				col = j;

				return true;
			}
		}
	}
	return false;
}

bool Board::isUnderAttack(int row , int col , Color by) const {
	for ( int i = 0; i < 8; i++ ) {
		for ( int j = 0; j < 8; j++ ) {

			Piece *attacker = grid [ i ][ j ];

			if ( attacker == nullptr ) {
				continue;
			}
			if ( attacker->getColor( ) != by ) {
				continue;
			}

			if ( attacker->isValidMove(i , j , row , col , grid) )
				return true;
		}
		return false;
	}
}

bool Board::isInCheck(Color color)const {
	int kingRow = -1;
	int kingCol = -1;

	for ( int i = 0; i < 8; i++ ) {
		for ( int j = 0; j < 8; j++ ) {

			Piece *piece = grid [ i ][ j ];

			if ( piece != nullptr && piece->getType( ) == PiecesType::KING &&
				piece->getColor( ) == color ) {
				kingRow = i;
				kingCol = j;
				break;
			}
		}
	}

	if ( kingRow == -1 )
		return false;
	Color opponent;

	if ( color == Color::WHITE ) {
		opponent = Color::BLACK;
	}
	else {
		opponent = Color::WHITE;
	}

	return isUnderAttack(kingRow , kingCol , opponent);
}

int Board::countPieces(Color color) const{
	int count = 0;

	for ( int i = 0; i < 8; i++ ) {
		for ( int j = 0; j < 8; j++ ) {
			Piece *piece = grid [ i ][ j ];

			if ( piece != nullptr && piece->getColor( ) == color ) {
				++count;
			}
		}
	}
	return count;
}

void Board::clearBoard( ) {
	for ( int i = 0; i < 8; i++ ) {
		for ( int j = 0; j < 8; j++ ) {
			delete grid [ i ][ j ];
			grid [ i ][ j ] = nullptr;
		}
	}
}

void Board::promotePawn(int row , int col , PiecesType newType) {
	Piece *pawn = grid [ row ][ col ];

	if ( pawn == nullptr ) {
		return;
	}

	if ( pawn->getType( ) != PiecesType::PAWN ) {
		return;
	}

	Color pawncolor = pawn->getColor( );

	delete pawn;

	switch ( newType ) {
		case PiecesType::QUEEN:
			grid [ row ][ col ] = new Queen(pawncolor);
			break;

		case PiecesType::ROOK:
			grid [ row ][ col ] = new Rook(pawncolor);
			break;

		case PiecesType::BISHOP:
			grid [ row ][ col ] = new Bishop(pawncolor);
			break;

		case PiecesType::KNIGHT:
			grid [ row ][ col ] = new Knight(pawncolor);
			break;

		default:
			
			grid [ row ][ col ] = new Queen(pawncolor);
			break;
	}

}


bool Board::isDraw( )const {
	int pieceCount = 0;

	for ( int i = 0; i < 8; i++ ) {
		for ( int j = 0; j < 8; j++ ) {

			if ( grid [ i ][ j ] != nullptr ) {
				++pieceCount;
			}
		}
	}
	return ( pieceCount == 2 );
}

Piece *const( *Board::getGrid( )const ) [ 8 ]{
	return grid;
}

void Board::display( )const {
	cout << "\n    a  b  c  d  e  f  g  h\n";
	cout << "  +------------------------+\n";

	for ( int i = 0; i < 8; i++ ) {
		cout << ( 8 - i ) << " | ";
		for ( int j = 0; j < 8; j++ ) {
			if ( grid [ i ][ j ] != nullptr ) {
				cout << grid [ i ][ j ]->getSymbol( ) << "  ";
			}
			else {
				cout << ".  ";
			}
		}
		cout << "| " << ( 8 - i ) << endl;

	}


	cout << "  +------------------------+\n";
	cout << "\n    a  b  c  d  e  f  g  h\n";
}


Board::~Board( ) {
	for ( int i = 0; i < 8; i++ ) {
		for ( int j = 0; j < 8; j++ ) {
			if ( grid [ i ][ j ] != nullptr ) {
				delete grid [ i ][ j ];
				grid [ i ][ j ] = nullptr;
			}
		}
	}
}
