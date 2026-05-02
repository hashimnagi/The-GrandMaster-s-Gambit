#include "Knight.h"

//Constructor
Knight::Knight(Color c) :Piece(c, PiecesType::KNIGHT) {};

//Getter for symbol virtual function in piece class
char Knight::getSymbol() const {
    if (color == Color::WHITE)
        return 'N';   // N for kNight
    else
        return 'n';
}
bool Knight::isValidMove(int initialrow, int initialcol, int finalrow, int finalcol, Piece* const board[8][8]) const {
    int rowdifference = abs(finalrow - initialrow);
    int coldifference = abs(finalcol - initialcol);

    // check L shape
    bool Lshape;
    if ((rowdifference == 2 && coldifference == 1) || (rowdifference == 1 && coldifference == 2))
        Lshape = true;
    else
        Lshape = false;

    if (Lshape == false)
        return false;

    // ← ADD THIS: bounds check before touching the board
    if (finalrow < 0 || finalrow >= 8 || finalcol < 0 || finalcol >= 8)
        return false;

    // check destination square
    Piece* destination = board[finalrow][finalcol];

    if (destination != nullptr && destination->getColor() == this->getColor())
        return false;

    return true;
}
