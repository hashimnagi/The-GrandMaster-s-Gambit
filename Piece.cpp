#include "Piece.h"

Piece::Piece(Color c, PiecesType T) : color(c), type(T) {};

Color Piece::getColor()const {
	return color;
}

PiecesType Piece::getType()const {
	return type;
}

bool Piece::getHasMoved()const {
	return HasMoved;
}

void Piece::setHasMoved(bool m) {
	HasMoved = m;
}
Piece:: ~Piece() {};

ostream& operator <<(ostream& os, const Piece& p) {
	os << p.getSymbol();
	return os;
}