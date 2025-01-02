#pragma once
#include <iostream>
#include <string>
#include "Piece.h"
#include "NullPiece.h"
#define SIDE_SIZE 8
class LogicalClac
{
public:
	static void findKingCordinates(int& kingX, int& kingY, const char checkedKing,	Piece*** board);
	static bool isPawnCheck(const int kingX, const int kingY, const bool whosTurn , Piece*** board);
	static bool isKnightnCheck(const int kingX, const int kingY, const char knight, Piece*** board);
	static bool isStrightDiagnleCheck(const int kingX, const int kingY, const char queen, const char rook, const char bishop,Piece*** board);
	static void convertMsgToCordinates(string msg, int& srcX, int& srcY, int& dstX, int& dstY);
	static void replaceNullWithNullObj(Piece*** board);
};
