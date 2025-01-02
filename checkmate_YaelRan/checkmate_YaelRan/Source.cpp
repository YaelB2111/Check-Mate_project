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
		amIGood = game.getBoard()[8*srcY+srcX]->IsMoveLegal(dstX, dstY, srcX, srcY, (const Piece**)game.getBoard(), resultCode, game.getWhosTurn());

		strcpy_s(msgToGraphics, "YOUR CODE"); // msgToGraphics should contain the result of the operation

		/******* JUST FOR EREZ DEBUGGING ******/
		int r = rand() % 10; // just for debugging......
		msgToGraphics[0] = (char)(1 + '0');
		msgToGraphics[1] = 0;
		/******* JUST FOR EREZ DEBUGGING ******/


		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}