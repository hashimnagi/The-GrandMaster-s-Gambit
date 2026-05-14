#pragma once

// standard library — alphabetical
#include <fstream>
#include <iostream>
#include <string>

// your own headers — alphabetical
#include "Types.h"
using namespace std;


class FileManager {
	private:
	string filename;
	//Converts our result enum into String so it can be stored
	string resultInString(const Result R);
	//Converts our Color result into string for storage
	string colorToString(const Color c);
	public:
		//Default value give to the filename in Constructor
	FileManager(string filename = "games.txt");
	//Save Record function
	void saveGame(const GameRecords &r);

	//display function for prevois games history
	void displayHistory( )const;

	//Getter Function for total gamed that have been played
	int getTotalGamesPlayed( )const;

	//Checks if the player has played the game before or not
	bool hasPlayerPlayed(const string &Playername)const;

};

