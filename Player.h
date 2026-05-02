#pragma once
#include "Types.h"
#include<string>

class Player {
	string Name;
	Color color;
	int captured;
public:
	//Parameterized Constructor
	Player(string n, Color c);

	//Getter Functions
	string GetName()const;
	Color GetColor()const;
	int GetCaptured()const;

	// Incrementung captured
	void IncreaseCaptured();

	//Display Function
	void DisplayInfo()const;
};

