#pragma once
#include<string>

using namespace std;

// ENUMS

//colors of the Peices
enum class Color {
	WHITE ,
	BLACK ,
	NONE
};

//PIECES TYPES

enum class PiecesType {
	KING ,
	QUEEN ,
	ROOK ,
	BISHOP ,
	KNIGHT ,
	PAWN ,
	NONE
};

//RESULTS

enum class Result {
	WHITE_WINS ,
	BLACK_WINS ,
	STALEMATE ,
	INSUFFICIENT_MATERIAL ,
	ONGOING
};

//TYPES OF MOVES
enum class MoveType {
	NORMAL ,
	CAPTURE ,
	CASTLING_KINGSIDE ,
	CASTLING_QUEENSIDE ,
	EN_PASSANT ,
	PROMOTION ,
	PROMOTION_CAPTURE
};

//UNION

union MoveData {
	
	//For promotion
	/*pawn ko promote karsaktain hain to Queen
	Rook or other pieces
	*/
	struct {
		PiecesType promotedTo; 
	}promotion;

	//For castling
	/* first hum check karain gay
	 kingside castle hay if false then else may queenside*/
	struct {
		bool kingSide;
	}castling;

	//En Passsant
	struct {
		int capturedPawnRow;
		int capturedPawnCol;
	}enPassant;

	MoveData( ) : promotion { PiecesType::NONE } {}

};

//STRUCTS
//struct may default public hay
struct Move {
	int fromtheRow;
	int fromtheCol;
	int totheRow;
	int totheCol;

	char pieceMoved;
	char pieceCaptured;

	MoveType type;
	MoveData data;

	string notation;

	//default constructor
	Move(): fromtheRow(0),fromtheCol(0),totheRow(0),
		totheCol(0),pieceMoved('.'),pieceCaptured('.'),
		type(MoveType::NORMAL),notation(""){}

	//Parametrized Constructor
	Move(int ftr , int ftc , int ttr , int ttc , char moved , char captured) :
		fromtheRow(ftr) , fromtheCol(ftc) , totheRow(ttr) , totheCol(ttc) ,
		pieceMoved(moved) , pieceCaptured(captured) ,
		type(MoveType::NORMAL) ,
		notation("") 
	{
		//notation meaning like e2 say e4 moves perform karna
		notation += char('a' + ftc);
		notation += char('0' + ( 8 - ftr ));
		notation += char('a' + ttc);
		notation += char('0' + ( 8 - ttr ));
	}
};

struct PlayerStats {
	string name;
	Color color;

	int capturedPieces;
	int totalMoves;

	PlayerStats( ) : name("") ,color(Color::NONE) ,
		capturedPieces(0) ,totalMoves(0) {}

	PlayerStats(string n , Color c) : name(n) ,color(c) ,
		capturedPieces(0) ,totalMoves(0) {}
};

struct GameRecords {
	string playerName1;
	string playerName2;
	string datePlayed;

	int totalMoves;
	Result result;

	//MAXIMUM NUMBER OF MOVES FOR SAFETY RAKHIN HAIN
	Move moveHistory [ 200 ];
	int moveCount;

	GameRecords( ) : playerName1("Unknown") , playerName2("Unknown") ,
		datePlayed("Unknown") , totalMoves(0) , result(Result::ONGOING) ,
		moveCount(0) {}
};