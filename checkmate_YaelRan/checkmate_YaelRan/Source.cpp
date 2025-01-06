/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project,
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include "Game.h"
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::string;


void main()
{
	srand(time_t(NULL));

	int srcX = 0, srcY = 0, dstX = 0, dstY = 0, resultCode = -1;
	std:string startBoardSymbles = "RNBKQBNRPPPPPPPP################################pppppppprnbkqbnr";
	char code = '0';
	Game game = Game(startBoardSymbles);
	Pipe p;
	bool isConnect = p.connect(), amIGood = false;

	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return;
		}
	}


	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	// YOUR CODE

	strcpy_s(msgToGraphics, "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0"); // just example...

	p.sendMessageToGraphics(msgToGraphics);   // send the board string
	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		LogicalClac::convertMsgToCordinates(msgFromGraphics, srcX, srcY, dstX, dstY);
		if (game.getBoard()[srcY][srcX]->IsMoveLegal(dstX, dstY, srcX, srcY, (const Piece***)game.getBoard(), resultCode, game.getWhosTurn()))
		{
			if (game.isCheck(srcX, srcY, dstX, dstY))
			{
				resultCode = SELF_CHECK;
			}
			else
			{
				game.getBoard()[srcY][srcX]->MovePlace(dstX, dstY, srcX, srcY, game.getBoard());
				game.nullPtrReplce();
				game.changeTurn();
			}
		}
		
		strcpy_s(msgToGraphics, to_string(resultCode).c_str()); // msgToGraphics should contain the result of the operation

		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}