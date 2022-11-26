/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project,
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>

using std::cin;
using std::cout;
using std::endl;
using std::string;

#define ZERO_ASCII 48

void main()
{
	srand(time_t(NULL));


	Pipe p;
	int moveCode = 0, startingColor = 0;
	bool isConnect = p.connect();
	Board board = Board();
	char answer[2] = { 0 };

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

	cout << "Which player is starting? (0 - white , other - black) : " << endl;
	cin >> startingColor;

	board.setColor(startingColor);

	strcpy_s(msgToGraphics, "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr"); 
	msgToGraphics[64] = (char) startingColor + ZERO_ASCII;
	msgToGraphics[65] = 0;

	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)
		try
		{
			moveCode = GamePiece::checkMovement(&board, msgFromGraphics);		//cheking the move
			//if the move is valid
			answer[0] = (char)moveCode + 48;									//forming the massege with the result code
			answer[1] = 0;
		}
		catch (int errorCode)													//if an error code was thrown , we catch it
		{
			cout << moveExceptions::what(errorCode) << endl;					//printing the error massege
			answer[0] = (char)errorCode + 48;									//forming the massege with the error code
			answer[1] = 0;
		}

		board.printBoard();														//printing the board state after the turn
		cout << endl;
		cout << endl;

		// return result to graphics		
		p.sendMessageToGraphics(answer);										//sending the reault to graphics

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}