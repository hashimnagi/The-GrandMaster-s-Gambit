#include "Player.h"
#include<iostream>
using namespace std;

//Parameterized Constructor
Player::Player(string n , Color c) : Name(n) , color(c) {};

//Getter Functions
string Player::GetName( )const {
	return Name;
}
Color Player::GetColor( )const {
	return color;
}

int Player::GetCaptured( )const {
	return captured;
}

// Incrementung captured
void Player::IncreaseCaptured( ) {
	captured++;
}

//Display Function
void Player::DisplayInfo( )const {
	cout << Name << "|";
	if ( color == Color::WHITE )
		cout << "WHITE";
	else
		cout << "BLACK";
	cout << "|Captured:" << captured << endl;
};