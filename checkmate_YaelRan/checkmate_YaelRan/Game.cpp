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
            ptr = new NullPiece(); // null piece
            *(this->_pieces + i) = ptr;
        }
        if (board[i] == 'p')
        {
            // ptr = new Pawn('p'); // white pawn
            *(this->_pieces + i) = ptr;
        }
        if (board[i] == 'P')
        {
            // ptr = new Pawn('P'); // black pawn
            *(this->_pieces + i) = ptr;
        }
        if (board[i] == 'n')
        {
            // ptr = new Knight('n'); // white Knight
            *(this->_pieces + i) = ptr;
        }
        if (board[i] == 'N')
        {
            // ptr = new Knight('N'); // black Knight
            *(this->_pieces + i) = ptr;
        }
        if (board[i] == 'b')
        {
            // ptr = new Bishop('b'); // white Bishop
            *(this->_pieces + i) = ptr;
        }
        if (board[i] == 'B')
        {
            // ptr = new Bishop('B'); // black Bishop
            *(this->_pieces + i) = ptr;
        }
        if (board[i] == 'r')
        {
            ptr = new Rook('r'); // white Rook
            *(this->_pieces + i) = ptr;
        }
        if (board[i] == 'R')
        {
            ptr = new Rook('R'); // black Rook
            *(this->_pieces + i) = ptr;
        }
        if (board[i] == 'q')
        {
            // ptr = new Queen('q'); // white Queen
            *(this->_pieces + i) = ptr;
        }
        if (board[i] == 'Q')
        {
            // ptr = new Queen('Q'); // black Queen
            *(this->_pieces + i) = ptr;
        }
        if (board[i] == 'k')
        {
            // ptr = new King('k'); // white King
            *(this->_pieces + i) = ptr;
        }
        if (board[i] == 'K')
        {
            // ptr = new King('K'); // black King
            *(this->_pieces + i) = ptr;
        }
    }
}

Game::~Game() //fix
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
	if (piececToMove->IsMoveLegal(x1, y1, x2, y2, (const Piece**)this->_pieces, rCode, this->_playsTurn))
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
	return rStr;
}

bool Game::isCheck()
{
	char checkedKing = !this->_playsTurn ? 'K' : 'k', knight = this->_playsTurn ? 'N' : 'n', queen = this->_playsTurn ? 'Q' : 'q', 
	rook = this->_playsTurn ? 'R' : 'r', bishop = this->_playsTurn ? 'B' : 'b', pawn = this->_playsTurn ? 'P' : 'p'; //change the true/false upper/lower to match the turn if needed
	
	int i = 0, j = 0, kingX = 0, kingY = 0, xCpy = kingX, yCpy = kingY;
	
	LogicalClac::findKingCordinates(kingX, kingY, checkedKing, this->_pieces); //find the cordinates of the prefered king
	
	//pawn check (check 2 possible check positions, and make sure no index out of range occures)
	if (LogicalClac::isPawnCheck(kingX, kingY, this->_playsTurn, this->_pieces)) 
	{
		return true;
	}

	//knightCheck - checks all the 8 possible knight check positions, (and make sure no index out of range occures) 
	if (LogicalClac::isKnightnCheck(kingX, kingY, knight, this->_pieces))
	{
		return true;
	}
	
	//knightCheck - checks all the 8 possible stright/diagnle check positions, (and make sure no index out of range occures) 
	if (LogicalClac::isStrightDiagnleCheck(kingX, kingY, queen, rook, bishop, this->_pieces))
	{
		return true;
	}

	return false;
}
