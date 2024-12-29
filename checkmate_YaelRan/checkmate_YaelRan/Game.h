#pragma once
#include "Piece.h"
#include "Rook.h"
#include "NullPiece.h"
#include <iostream>
#include <string>

#define SIDE_SIZE 8
class Game
{
public:
	Game(string board); //c'tor
	~Game(); //d'tor
	void TryMove(const int x1, const int y1, const int x2, const int y2);
	std::string boardState() const;
	//manageGame - probably useless
	bool isCheck();

private:
	unsigned int _side;
	bool _playsTurn; //black -> false |  white -> true 
	Piece** _pieces;
};