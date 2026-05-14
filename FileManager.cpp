#include "FileManager.h"
using namespace std;

	//Default value give to the filename in Constructor
FileManager::FileManager(string filename)  
{
	this->filename = filename;
}
string FileManager::resultInString(Result result) {
	if ( result == Result::WHITE_WINS )
		return "White Wins";
	else if ( result == Result::BLACK_WINS )
		return "Black Wins";
	else if ( result == Result::STALEMATE )
		return "Stalemate";
	else
		return "Ongoing";
}
// Add to FileManager.cpp:
string FileManager::colorToString(const Color c) {
	if ( c == Color::WHITE )
		return "White";
	else if ( c == Color::BLACK )
		return "Black";
	else
		return "None";
}
	//Save Record function
void FileManager::saveGame(const GameRecords &r) {
	ofstream write;
	write.open(filename , ios::app);
	if ( write.is_open( ) ) {
		write << "DATE: " << r.datePlayed << "\n";
		write << "WHITE: " << r.playerName1 << "\n";
		write << "BLACK: " << r.playerName2 << "\n";
		write << "RESULT: " << resultInString(r.result) << "\n";

		for ( int i = 0; i < r.moveCount; i++ ) {
			write << r.moveHistory [ i ].notation << " ";
		}
		write << endl;
		write.close( );
	}
}

//display function for previous games history
void FileManager::displayHistory( )const {
	ifstream read;
	string line;
	read.open(filename);
	if ( !read.is_open( ) ) {
		cout << "no history found." << endl;
		return;
	}
	while ( getline(read , line) ) {
		cout << line << endl;
	}
	read.close( );
}


//Getter Function for total gamed that have been played We count the total number of the word DATE in thwe file
int FileManager::getTotalGamesPlayed( )const {
	ifstream read;
	read.open(filename);
	string line;
	int count = 0;
	while ( getline(read , line) ) {
		if ( line.find("DATE") != string::npos ) {
			count++;
		}
	}
	return count;
}

	//Checks if the player has played the game before or not
bool FileManager::hasPlayerPlayed(const string &Playername)const {
	ifstream read;
	string line;
	read.open(filename);
	if ( !read.is_open( ) )
		return false;
	while ( getline(read , line) ) {
		if ( line.find(Playername) != string::npos ) {
			read.close( );
			return true;
		}
	}
	read.close( );
	return false;
}
