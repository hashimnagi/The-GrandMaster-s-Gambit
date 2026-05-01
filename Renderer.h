#pragma once
#include<SFML/Graphics.hpp>
#include"Board.h"
#include"Types.h"
#include<Vector>
#include<string>

using namespace std;

class Renderer {
	private:
	sf::RenderWindow win;
	sf::Texture piecesTexture [ 12 ];
	sf::Font font;

	//Board Dimensions
	static const int TILE_SIZE = 80; //each sqaure pixels
	static const int BOARD_PX = 640; //8*80
	static const int SIDE_BAR = 240;
	static const int WINDOW_W = BOARD_PX + SIDE_BAR;
	static const int WINDOW_H = BOARD_PX;  

	//Icy Sea Theme (color oalletes)
	sf::Color lightTile { 235, 233, 214 }; //Ivory
	sf::Color darkTile { 119, 149, 186 }; //Steel Blue
	sf::Color hlColors { 247 , 247 , 105 , 190 }; //light yellow highlight
	sf::Color dotColor { 0,0,0,80 }; //valid move dot
	sf::Color capdot { 220 , 50 , 50 , 170 };
	sf::Color sidebarBig { 54, 69, 79 }; //charcol black
	sf::Color whiteText { 240,240,240 };  
	sf::Color textColor { 248,250,252 };

	//Private Helpers

	int getTextureIndex(PiecesType type , Color color)const;
	void drawBoard(int selRow , int selCol);
	void drawPieces(const Board &board);
	void drawValidDots(const Board &board ,
					const vector<pair<int , int>> &moves);
	void drawSideBar(const string &p1Name , const string &p2Name ,
					 Color currentTurn , int p1Captures ,
					 int p2Captures , bool inCheck);

	public:
	Renderer( );

	//for loading fonts and textures-call before game loop
	bool loadAssets( );

	bool isOpen( )const;

	//Main render call , called every frame

	void render(const Board &board , int selRow , int selCol ,
				const vector<pair<int , int>> &validMoves ,
				const string &p1Name , const string &p2Name ,
				Color currentTuen , int p1Captures , int p2Captures ,
				bool inCheck);

	//Converting pixels click to board tile{row , col}
	//if we click outside the board it will return {-1,-1}

	pair<int , int > getTileClicked(int pixelX , int pixelY)const;

	//return false if the window is closed
	bool pollEvents(pair<int , int> &clickedTile);


};
