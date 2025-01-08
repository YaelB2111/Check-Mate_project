#include "Game.h"

Game::Game(std::string board) : _side(SIDE_SIZE), _playsTurn(true)
{
	Piece* ptr = nullptr;
	int i = 0, j = 0, idxStrBoard = 0;
	this->_pieces = new Piece **[SIDE_SIZE];
    for (i = 0; i < SIDE_SIZE; i++)
    {
        this->_pieces[i] = new Piece * [SIDE_SIZE];
        for (j = 0; j < SIDE_SIZE; j++)
        {
            if (board[idxStrBoard] == '#')
            {
                ptr = new NullPiece(); // null piece
            }
            if (board[idxStrBoard] == 'p')
            {
                ptr = new Pawn('p'); // white pawn
            }
            if (board[idxStrBoard] == 'P')
            {
                ptr = new Pawn('P'); // black pawn
            }
            if (board[idxStrBoard] == 'n')
            {
                ptr = new Knight('n'); // white Knight
            }
            if (board[idxStrBoard] == 'N')
            {
                ptr = new Knight('N'); // black Knight
            }
            if (board[idxStrBoard] == 'b')
            {
                ptr = new Bishop('b'); // white Bishop
            }
            if (board[idxStrBoard] == 'B')
            {
                ptr = new Bishop('B'); // black Bishop
            }
            if (board[idxStrBoard] == 'r')
            {
                ptr = new Rook('r'); // white Rook
            }
            if (board[idxStrBoard] == 'R')
            {
                ptr = new Rook('R'); // black Rook
            }
            if (board[idxStrBoard] == 'q')
            {
                ptr = new Queen('q'); // white Queen
            }
            if (board[idxStrBoard] == 'Q')
            {
                ptr = new Queen('Q'); // black Queen
            }
            if (board[idxStrBoard] == 'k')
            {
                ptr = new King('k'); // white King
            }
            if (board[idxStrBoard] == 'K')
            {
                ptr = new King('K'); // black King
            }
            this->_pieces[i][j] = ptr;
            idxStrBoard++;
        }
    }
}

Game::~Game() //fix
{
	int i = 0, j = 0;
	for (i = 0; i < SIDE_SIZE; i++)
	{
        for (j = 0; j < SIDE_SIZE; j++)
        {
            delete this->_pieces[i][j];
        }
	}
	if (this->_pieces != nullptr)
	{
		delete[] this->_pieces;
	}
}

void Game::TryMove(int x1, int y1, int x2, int y2)
{
	Piece* piececToMove = this->_pieces[x1][y1];
	Piece* piececToSwap = this->_pieces[x2][y2];
	Piece* temp = piececToMove;
	int rCode = 0;
	if (piececToMove->IsMoveLegal(x1, y1, x2, y2, (const Piece***)this->_pieces, rCode, this->_playsTurn, true))
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
			rStr += this->_pieces[i][j]->GetName() + " ";
		}
		rStr += "\n";
	}
	return rStr;
}

bool Game::isCheck(int srcX, int srcY, int dstX, int dstY, bool selfCheck)
{
    return LogicalClac::checkCheck(srcX, srcY, dstX, dstY, this->getWhosTurn(), selfCheck, this->getBoard());
}

bool Game::isMate(bool whitePlays)
{
    int kingX = 0, kingY = 0;
    return LogicalClac::mateCheck(kingX, kingY, whitePlays, this->getBoard());
}

Piece*** Game::getBoard() const
{
    return this->_pieces;
}

bool Game::getWhosTurn() const
{
    return this->_playsTurn;
}

void Game::changeTurn()
{
    this->_playsTurn = !this->getWhosTurn();
}

void Game::nullPtrReplce()
{
    LogicalClac::replaceNullWithNullObj(this->getBoard());
}
