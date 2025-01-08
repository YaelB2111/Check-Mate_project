#include "LogicalClacUtils.h"

void LogicalClac::findKingCordinates(int& kingX, int& kingY, const char checkedKing, Piece*** board)
{
	int i = 0, j = 0;
	bool finished = false;
	for (i = 0; i < SIDE_SIZE && !finished; i++) //find the cordinates of the prefered king
	{
		for (j = 0; j < SIDE_SIZE && !finished; j++)
		{
			if (board[i][j]->GetName() == checkedKing)
			{
				kingX = j;
				kingY = i;
				finished = true;
			}
		}
	}
}



bool LogicalClac::isPawnCheck(const int kingX, const int kingY, const bool whosTurn, Piece*** board)
{
	//pawn check
	if (!whosTurn) //white played - black king check
	{
		if (kingY > 0 && kingY < SIDE_SIZE - 1 && kingX < SIDE_SIZE - 1 && kingX > 0 && (board[kingY - 1][kingX + 1]->GetName() == 'P' || board[kingY - 1][kingX - 1]->GetName() == 'P'))
		{
			return true;
		}
	}
	else //black played - white king check
	{
		if (kingY > 0 && kingY < SIDE_SIZE - 1 && kingX < SIDE_SIZE - 1 && kingX > 0 && (board[kingY + 1][kingX + 1]->GetName() == 'p' || board[kingY + 1][kingX - 1]->GetName() == 'p'))
		{
			return true;
		}
	}
	return false;
}

bool LogicalClac::isKingCheck(const int kingX, const int kingY, const char king, Piece*** board)
{
	bool rightCheck = kingX < SIDE_SIZE - 1, leftCheck = kingX > 0, upCheck = kingY < SIDE_SIZE - 1, downCheck = kingY > 0;
	if (upCheck) //up
	{
		if (board[kingY + 1][kingX]->GetName() == king)
		{
			return true;
		}
		if (rightCheck && board[kingY + 1][kingX + 1]->GetName() == king) //up right
		{
			return true;
		}
		if (leftCheck && board[kingY + 1][kingX - 1]->GetName() == king) //up left
		{
			return true;
		}
	}
	if (downCheck) //down
	{
		if (board[kingY - 1][kingX]->GetName() == king)
		{
			return true;
		}
		if (rightCheck && board[kingY - 1][kingX + 1]->GetName() == king) //down right
		{
			return true;
		}
		if (leftCheck && board[kingY - 1][kingX - 1]->GetName() == king) //down left
		{
			return true;
		}
	}
	if (rightCheck && board[kingY][kingX + 1]->GetName() == king) //right
	{
		return true;
	}
	if (leftCheck && board[kingY][kingX - 1]->GetName() == king) //left
	{
		return true;
	}
	return false;
}

bool LogicalClac::isKnightnCheck(const int kingX, const int kingY, const char knight, Piece*** board)
{
	//knightCheck - checks all the 8 possible knight check positions, (and make sure no index out of range occures) 
	if (kingX < SIDE_SIZE - 2) //right
	{
		if (kingY < SIDE_SIZE - 1 && board[kingY + 1][kingX + 2]->GetName() == knight) //right up
		{
			return true;
		}
		if (kingY > 0 && board[kingY - 1][kingX + 2]->GetName() == knight) //right down
		{
			return true;
		}
	}
	if (kingX >= 2) //left
	{
		if (kingY < SIDE_SIZE - 1 && board[kingY + 1][kingX - 2]->GetName() == knight) //left up
		{
			return true;
		}
		if (kingY > 0 && board[kingY - 1][kingX - 2]->GetName() == knight) //left down
		{
			return true;
		}
	}
	if (kingY < SIDE_SIZE - 2) //up
	{
		if (kingX < SIDE_SIZE - 1 && board[kingY + 2][kingX + 1]->GetName() == knight) //up right
		{
			return true;
		}
		if (kingX > 0 && board[kingY + 2][kingX - 1]->GetName() == knight) //up left
		{
			return true;
		}
	}
	if (kingY >= 2) //down
	{
		if (kingX < SIDE_SIZE - 1 && board[kingY - 2][kingX + 1]->GetName() == knight) //down right
		{
			return true;
		}
		if (kingX > 0 && board[kingY - 2][kingX - 1]->GetName() == knight) //down left
		{
			return true;
		}
	}
	return false;
}

bool LogicalClac::isStrightDiagnleCheck(const int kingX, const int kingY, const char queen, const char rook, const char bishop, Piece*** board)
{
	int i = 0;
	bool rightStright = true, leftStright = true, upStright = true, downStright = true,
		upDiagRight = true, upDiagLeft = true, downDiagRight = true, downDiagLeft = true;
	for (i = 1; i < SIDE_SIZE; i++) //quenn, rook & bishop check
	{
		if (kingX + i < SIDE_SIZE) //right checks
		{
			if (rightStright && board[kingY][kingX + i]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				rightStright = false;
				if (board[kingY][kingX + i]->GetName() == queen || board[kingY][kingX + i]->GetName() == rook) //stright
				{
					return true;
				}
			}
		}
		if (kingX - i >= 0) //left checks
		{
			if (leftStright && board[kingY][kingX - i]->GetName() != '#')  //checks if not blocked already and not NullPiece
			{
				leftStright = false;
				if (board[kingY][kingX - i]->GetName() == queen || board[kingY][kingX - i]->GetName() == rook) //stright
				{
					return true;
				}
			}
		}
		if (kingY + i < SIDE_SIZE) //up checks
		{
			if (upStright && board[kingY + i][kingX]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				upStright = false;
				if (board[kingY + i][kingX]->GetName() == queen || board[kingY + i][kingX]->GetName() == rook) //stright
				{
					return true;
				}
			}
			if (kingX - i >= 0 && upDiagLeft && board[kingY + i][kingX - i]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				upDiagLeft = false;
				if (board[kingY + i][kingX - i]->GetName() == queen || board[kingY + i][kingX - i]->GetName() == bishop) //diagnle left
				{
					return true;
				}
			}
			if (kingX + i < SIDE_SIZE && upDiagRight && board[kingY + i][kingX + i]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				upDiagRight = false;
				if (board[kingY + i][kingX + i]->GetName() == queen || board[kingY + i][kingX + i]->GetName() == bishop) //diagnle right
				{
					return true;
				}
			}
			
		}
		if (kingY - i >= 0) //down checks
		{
			if (downStright && board[kingY - i][kingX]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				downStright = false;
				if (board[kingY - i][kingX]->GetName() == queen || board[kingY - i][kingX]->GetName() == rook) //stright
				{
					return true;
				}
			}
			if (kingX + i < SIDE_SIZE && downDiagRight && board[kingY - i][kingX + i]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				downDiagRight = false;
				if (board[kingY - i][kingX + i]->GetName() == queen || board[kingY - i][kingX + i]->GetName() == bishop) //diagnle right
				{
					return true;
				}
			}
			if (kingX - i >= 0 && downDiagLeft && board[kingY - i][kingX - i]->GetName() != '#') //checks if not blocked already and not NullPiece)
			{
				downDiagLeft = false;
				if (board[kingY - i][kingX - i]->GetName() == queen || board[kingY - i][kingX - i]->GetName() == bishop) //diagnle left
				{
					return true;
				}
			}
		}
	}
	return false;
}

void LogicalClac::convertMsgToCordinates(string msg, int& srcX, int& srcY, int& dstX, int& dstY)
{
	srcX = int(msg[0])-'a';
	srcY = int(msg[1]) - '1';
	dstX = int(msg[2]) - 'a';
	dstY = int(msg[3]) - '1';
}

void LogicalClac::replaceNullWithNullObj(Piece*** board)
{
	int i = 0, j = 0;
	bool replaced = false;
	for (i = 0; i < SIDE_SIZE && !replaced; i++)
	{
		for (j = 0; j < SIDE_SIZE && !replaced; j++)
		{
			if (board[i][j] == nullptr)
			{
				board[i][j] = new NullPiece();
				replaced = true;
			}
		}
	}
}

void LogicalClac::castling(const int srcX, const int srcY, const int dstX, const int dstY, Piece*** board)
{
	Piece* temp = nullptr;
	if (dstX == 0)
	{
		temp = board[srcY][srcX]; //King
		board[srcY][srcX] = board[srcY][0];
		board[srcY][3] = temp;
		temp = board[dstY][dstX]; //Rook
		board[dstY][dstX] = board[srcY][1];
		board[srcY][4] = temp;
	}
	else
	{
		temp = board[srcY][srcX]; //King
		board[srcY][srcX] = board[srcY][6];
		board[srcY][6] = temp;
		temp = board[dstY][dstX]; //Rook
		board[dstY][dstX] = board[srcY][5];
		board[srcY][5] = temp;
	}
}

void LogicalClac::printBoard(Piece*** board)
{
	int i = 0, j = 0;
	system("CLS");
	std::cout << "+-----+-----+-----+-----+-----+-----+-----+-----+" << std::endl;
	for (i = 7; i >= 0; i--)
	{
		std::cout << "|  ";
		for (j = 0; j < SIDE_SIZE; j++)
		{
				std::cout << board[i][j]->GetName() << "  |  ";
		}           
		std::cout << "\n+-----+-----+-----+-----+-----+-----+-----+-----+\n";
		//std::cout << "|                                             |" << std::endl;
	}
}

void LogicalClac::simulateMove(const int srcX, const int srcY, const int dstX, const int dstY, Piece*** board)
{
	bool checkResult = false;
	Piece* scrPiece = board[srcY][srcX];
	Piece* dstPiece = board[dstY][dstX];

	board[srcY][srcX] = new NullPiece();
	board[dstY][dstX] = scrPiece;

	free(board[srcY][srcX]);
	board[srcY][srcX] = scrPiece;
	board[dstY][dstX] = dstPiece;
}

bool LogicalClac::checkCheck(int srcX, int srcY, int dstX, int dstY, bool whitePlays, bool selfCheck, Piece*** board)
{
	char checkedKing = !whitePlays ? 'k' : 'K', knight = whitePlays ? 'n' : 'N', queen = whitePlays ? 'q' : 'Q',
		rook = whitePlays ? 'r' : 'R', bishop = whitePlays ? 'b' : 'B', pawn = whitePlays ? 'p' : 'P'; //change the true/false upper/lower to match the turn if needed

	int i = 0, j = 0, kingX = 0, kingY = 0;
	Piece* scrPiece = board[srcY][srcX];
	Piece* dstPiece = board[dstY][dstX];

	if (selfCheck)
	{
		board[srcY][srcX] = new NullPiece();
		board[dstY][dstX] = scrPiece;
	}


	LogicalClac::findKingCordinates(kingX, kingY, checkedKing, board); //find the cordinates of the prefered king

	//pawn check (check 2 possible check positions, and make sure no index out of range occures)
	if (LogicalClac::isPawnCheck(kingX, kingY, whitePlays, board))
	{
		if (selfCheck)
		{
			free(board[srcY][srcX]);
			board[srcY][srcX] = scrPiece;
			board[dstY][dstX] = dstPiece;
		}
		return true;
	}

	//king check (8 possible checks)
	if (LogicalClac::isKingCheck(kingX, kingY, whitePlays ? 'k' : 'K', board)) //!this->_playsTurn ? 'k' : 'K' ---> opposite king
	{
		if (selfCheck)
		{
			free(board[srcY][srcX]);
			board[srcY][srcX] = scrPiece;
			board[dstY][dstX] = dstPiece;
		}
		return true;
	}

	//knightCheck - checks all the 8 possible knight check positions, (and make sure no index out of range occures) 
	if (LogicalClac::isKnightnCheck(kingX, kingY, knight, board))
	{
		if (selfCheck)
		{
			free(board[srcY][srcX]);
			board[srcY][srcX] = scrPiece;
			board[dstY][dstX] = dstPiece;
		}
		return true;
	}

	//knightCheck - checks all the 8 possible stright/diagnle check positions, (and make sure no index out of range occures) 
	if (LogicalClac::isStrightDiagnleCheck(kingX, kingY, queen, rook, bishop, board))
	{
		if (selfCheck)
		{
			free(board[srcY][srcX]);
			board[srcY][srcX] = scrPiece;
			board[dstY][dstX] = dstPiece;
		}
		return true;
	}

	if (selfCheck)
	{
		free(board[srcY][srcX]);
		board[srcY][srcX] = scrPiece;
		board[dstY][dstX] = dstPiece;
	}
	return false;
}

bool LogicalClac::mateCheck(int kingX, int kingY, const bool whitePlays, Piece*** board)
{
	Piece* temp = nullptr;
	char king = whitePlays ? 'K' : 'k';
	LogicalClac::findKingCordinates(kingX, kingY, king, board);
	bool rightCheck = kingX < SIDE_SIZE - 1, leftCheck = kingX > 0, upCheck = kingY < SIDE_SIZE - 1, downCheck = kingY > 0;
	int result = 0;
	if (upCheck) //up
	{
		if (board[kingY][kingX]->IsMoveLegal(kingX, kingY + 1, kingX, kingY, (const Piece***)board, result, whitePlays, true) &&
			!checkCheck(kingX, kingY, kingX, kingY + 1, whitePlays, true, board))
		{
			return false;
		}
		if (rightCheck && board[kingY][kingX]->IsMoveLegal(kingX + 1, kingY + 1, kingX, kingY, (const Piece***)board, result, whitePlays, true) &&
			!checkCheck(kingX, kingY, kingX + 1, kingY + 1, whitePlays, true, board)) //up right
		{
			return false;
		}
		if (leftCheck && board[kingY][kingX]->IsMoveLegal(kingX - 1, kingY + 1, kingX, kingY, (const Piece***)board, result, whitePlays, true) &&
			!checkCheck(kingX, kingY, kingX - 1, kingY + 1, whitePlays, true, board)) //up left
		{
			return false;
		}
	}
	if (downCheck) //down
	{
		if (board[kingY][kingX]->IsMoveLegal(kingX, kingY - 1, kingX, kingY, (const Piece***)board, result, whitePlays, true) &&
			!checkCheck(kingX, kingY, kingX, kingY - 1, whitePlays, true, board))
		{
			return false;
		}
		if (rightCheck && board[kingY][kingX]->IsMoveLegal(kingX + 1, kingY - 1, kingX, kingY, (const Piece***)board, result, whitePlays, true) &&
			!checkCheck(kingX, kingY, kingX + 1, kingY - 1, whitePlays, true, board)) //down right
		{
			return false;
		}
		if (leftCheck && board[kingY][kingX]->IsMoveLegal(kingX - 1, kingY - 1, kingX, kingY, (const Piece***)board, result, whitePlays, true) &&
			!checkCheck(kingX, kingY, kingX - 1, kingY - 1, whitePlays, true, board)) //down left
		{
			return false;
		}
	}
	if (rightCheck && board[kingY][kingX]->IsMoveLegal(kingX+1, kingY, kingX, kingY, (const Piece***)board, result, whitePlays, true) &&
		!checkCheck(kingX, kingY, kingX + 1, kingY, whitePlays, true, board)) //right
	{
		return false;
	}
	if (leftCheck && board[kingY][kingX]->IsMoveLegal(kingX-1, kingY, kingX, kingY, (const Piece***)board, result, whitePlays, true) &&
		!checkCheck(kingX, kingY, kingX - 1, kingY, whitePlays, true, board)) //left
	{
		return false;
	}
	return true;
}


bool LogicalClac::isCastling(const int srcX, const int srcY, const int dstX, const int dstY, Piece*** board)
{
	if ((board[srcY][srcX]->GetName() == 'K' && board[dstY][dstX]->GetName() == 'R' ||
		 board[srcY][srcX]->GetName() == 'k' && board[dstY][dstX]->GetName() == 'r'))
	{
		Rook* rook = (Rook*)board[dstY][dstX];
		King* king = (King*)board[srcY][srcX];
		if (!rook->GetMoved() && !king->GetMoved())
		{
			return true;
		}
	}
	return false;
}

