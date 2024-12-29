#pragma once
#include "Piece.h"
#include <iostream>

#define SIDE_SIZE 8
class Game
{
public:
	Game(std::string board); //c'tor
	~Game(); //d'tor


private:
	unsigned int _side;
	bool _playsTurn; //white -> false | black -> true 
	Piece** _pieces;
};