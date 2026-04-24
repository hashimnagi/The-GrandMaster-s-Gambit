#pragma once
#include <iostream>
#include "Types.h"
using namespace std;

//Abstract Class so pure virtual functions included
class Piece {
protected:
	Color color;
	PiecesType type;
	bool HasMoved;
public:
	Piece(Color c, PiecesType T);

	//Pure Virtual Functions

	virtual bool isValidMove() = 0;
	virtual char getSymbol() const = 0;

    //Getters
	Color getColor()const;
	PiecesType getType()const;
	bool getHasMoved()const;

	//Setter
	void setHasMoved(bool m);

	//Virtual destructor
	virtual ~Piece();
	
	//Overloaded friend operator
	friend ostream& operator <<(ostream& os, const Piece& p);

};