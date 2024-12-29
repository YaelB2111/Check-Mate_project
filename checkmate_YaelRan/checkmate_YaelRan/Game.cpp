#include "Game.h"

Game::Game(std::string board) : _side(SIDE_SIZE), _playsTurn(true)
{
	Piece* ptr = nullptr;
	int i = 0;
	this->_pieces = new Piece * [SIDE_SIZE * SIDE_SIZE];
	for (i = 0; i < SIDE_SIZE * SIDE_SIZE; i++)
	{
		if (board[i] == '#')
		{
			//ptr = new NullPiece(); //null piece
			*(this->_pieces + i) = ptr;
		}
		if (board[i] == 'p')
		{
			//ptr = new Pawn("P"); //white pawm
			*(this->_pieces + i) = ptr;
		}
		if (board[i] == 'P')
		{
			//ptr = new Pawn("P"); //black pawm
			*(this->_pieces + i) = ptr;
		}
		if (board[i] == 'k')
		{
			//ptr = new Knight("k"); //white Knight
			*(this->_pieces + i) = ptr;
		}
		if (board[i] == 'K')
		{
			//ptr = new Knight("K"); //black Knight
			*(this->_pieces + i) = ptr;
		}
		if (board[i] == 'b')
		{
			//ptr = new Bishop("b"); //white Bishop
			*(this->_pieces + i) = ptr;
		}
		if (board[i] == 'B')
		{
			//ptr = new Bishop("B"); //black Bishop
			*(this->_pieces + i) = ptr;
		}
		if (board[i] == 'q')
		{
			//ptr = new Queen("q"); //white Queen
			*(this->_pieces + i) = ptr;
		}
		if (board[i] == 'Q')
		{
			//ptr = new Queen("Q"); //black Queen
			*(this->_pieces + i) = ptr;
		}
		if (board[i] == 'k')
		{
			//ptr = new King("k"); //white King
			*(this->_pieces + i) = ptr;
		}
		if (board[i] == 'K')
		{
			//ptr = new King("K"); //black King
			*(this->_pieces + i) = ptr;
		}
	}
}

Game::~Game()
{
	int i = 0;
	for (i = 0; i < SIDE_SIZE * SIDE_SIZE; i++)
	{
		if (*(this->_pieces + i) != nullptr)
		{
			delete *(this->_pieces + i);
		}
	}
	if (this->_pieces != nullptr)
	{
		delete[] this->_pieces;
	}
}

void Game::TryMove(int x1, int y1, int x2, int y2)
{
	Piece* piececToMove = this->_pieces[x1, y1];
	Piece* piececToSwap = this->_pieces[x2, y2];
	Piece* temp = piececToMove;
	int rCode = 0;
	if (piececToMove->IsMoveLegal(x1, y1, x2, y2, this->_pieces, rCode, this->_playsTurn))
	{
		piececToMove = piececToSwap;
		piececToSwap = temp;
	}
}

std::string Game::boardState() const
{
	string rStr = "";
	int i = 0, j = 0;
	for (i = 0; i < SIDE_SIZE; i++)
	{
		for (j = 0; j < SIDE_SIZE; i++)
		{
			rStr += this->_pieces[i, j]->GetName() + " ";
		}
		rStr += "\n";
	}
	return ;
}
