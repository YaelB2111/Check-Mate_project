#pragma once
#include <iostream>
#include <string>
#include "Piece.h"
#include "NullPiece.h"
#include "Rook.h"
#include "King.h"
#define SIDE_SIZE 8
class LogicalClac
{
public:
	static void findKingCordinates(int& kingX, int& kingY, const char checkedKing,	Piece*** board);
	static bool isPawnCheck(const int kingX, const int kingY, const bool whosTurn , Piece*** board);
	static bool isKingCheck(const int kingX, const int kingY, const char king, Piece*** board);
	static bool isKnightnCheck(const int kingX, const int kingY, const char knight, Piece*** board);
	static bool isStrightDiagnleCheck(const int kingX, const int kingY, const char queen, const char rook, const char bishop,Piece*** board);
	static void convertMsgToCordinates(string msg, int& srcX, int& srcY, int& dstX, int& dstY);
	static void replaceNullWithNullObj(Piece*** board);
	static bool isCastling(const int srcX, const int srcY, const int dstX, const int dstY, Piece*** board);
	static void castling(const int srcX, const int srcY, const int dstX, const int dstY, Piece*** board);
	static void printBoard(Piece*** board);
};
