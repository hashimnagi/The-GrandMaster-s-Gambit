#pragma once

#include"Bishop.h"
#include"King.h"
#include"Knight.h"
#include"Pawn.h"
#include"Piece.h"
#include"Queen.h"
#include"Rook.h"
#include<iostream>

class Board {
	private:
	Piece *grid [ 8 ][ 8 ];

	public:
	Board( );
	
	void intiailize( );
	Piece *getPiece(int row , int col)const;
	void setPiece(int row , int col , Piece *piece);
	Piece *movePiece(int fromtheRow , int fromtheCol , int totheRow , int totheCol);
	bool isInBounds(int row , int col)const;
	bool isUnderAttack(int row , int col , Color by) const;
	bool isInCheck(Color color) const;
	int countPieces(Color color) const;
	void clearBoard( );
	void promotePawn(int row , int col , PiecesType newType);
	bool isDraw( ) const;
	bool findKing(Color color , int &row , int &col)const;
	void display( )const;

	Piece *const ( *getGrid( ) const ) [ 8 ];

	~Board( );
};
