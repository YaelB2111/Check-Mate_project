#pragma once
#include <iostream>
#include <string>
#include <cctype>

#define INVALID -1
#define VALID_MOVE 0
#define TO_CHECK_MOVE 1
#define NO_PIECE_SRC 2
#define PIECE_DST 3
#define SELF_CHECK 4
#define OUT_OF_BOUND 5
#define INVALID_MOVE 6
#define SRC_DST_EQUAL 7
#define CHECK_MOVE 8


#define SIZE 8

using namespace std;
class Piece
{
public:
	Piece(const char name);
	~Piece();
	char GetName() const;
	void MovePlace(const int destX, const int destY, const int srcX, const int srcY, Piece** board[]);
	bool IsSelfCheck(const int srcX, const int srcY, const Piece*** board, const bool whitePlays);
	void Eat(const int destX, const int destY, const int srcX, int srcY, Piece*** board);
	virtual bool IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece*** board, int& result, bool whitePlays, const bool move) = 0;
	
private:
	char _name;

};

