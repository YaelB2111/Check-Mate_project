#pragma once

#define SIDE_SIZE 8
class LogicalClac
{
public:
	static void findKingCordinates(int& kingX, int& kingY, const string checkedKing, const Piece** board);
	static bool isPawnCheck(const int kingX, const int kingY, const bool whosTurn ,const Piece** board);
	static bool isKnightnCheck(const int kingX, const int kingY, const string knight,const Piece** board);
};