#include "Board.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Queen.h"
#include "Rook.h"
#include "Pawn.h"

/*
This method is a c'tor for the board.
Input: None.
Output: None.
*/

Board::Board() : _currColor(-1), _lastPawnToDoubleStep(0), _isLastTurnWasDoubleStep(0)	//initializing most of the fields 
{
	int i = 0 , k = 1;
	string currLocation = "aa";

	_player1 = new GamePiece * [NUM_OF_PIECES_PER_COLOR];								//creating the white pieces array
	_player2 = new GamePiece * [NUM_OF_PIECES_PER_COLOR];								//creating the black pieces array

	_layout = "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0\0";	//initializing the layout string

	for (i = 0; i < NUM_OF_PIECES_PER_COLOR; i++)										//initializing the arrays accroding to the string
	{
		currLocation[COL] = (char) ((i % 8) + 97);										//current colom
		currLocation[ROW] = (char) k + 48;												//current row

		if(i == (NUM_OF_PIECES_PER_COLOR / 2) - 1)										//of we moved to the seconed row
		{
			k ++;
		}

		switch (_layout[i])																//creating two objects according to the string
		{
		case 'r':																		//for rook
			_player2[i] = new Rook(currLocation);										//creating black rook
			currLocation[ROW] += 7;														//offsetting the location by 7
			_player1[i] = new Rook(currLocation);										//creating white rook
			break;
		case 'n':																		//for knight
			_player2[i] = new Knight(currLocation);										//creating black knight
			currLocation[ROW] += 7;														//offsetting the location by 7
			_player1[i] = new Knight(currLocation);										//creating white knight
			break;
		case 'b':																		//for bishop
			_player2[i] = new Bishop(currLocation);										//creating black bishop
			currLocation[ROW] += 7;														//offsetting the location by 7
			_player1[i] = new Bishop(currLocation);										//creating white bishop
			break;
		case 'q':																		//for queen
			_player2[i] = new Queen(currLocation);										//creating black queen
			currLocation[ROW] += 7;														//offsetting the location by 7
			_player1[i] = new Queen(currLocation);										//creating white queen
			break;
		case 'k':																		//for king
			_player2[i] = new King(currLocation);										//creating black king
			currLocation[ROW] += 7;														//offsetting the location by 7
			_player1[i] = new King(currLocation);										//creating white king
			break;
		case 'p':																		//for pawn
			_player2[i] = new Pawn(currLocation, 1);									//creating black pawn
			currLocation[ROW] += 5;														//offsetting the location by 5
			_player1[i] = new Pawn(currLocation , 0);									//creating white pawn
			break;
		default:
			break;
		}
	}
}

/*
This method is a d'tor for the board.
Input: None.
Output: None.
*/

Board::~Board()
{
	delete(_player1);																	//freeing the memory of the two arrays
	delete(_player2);
}

/*
This method returns the board layout.
Input: None.
Output: The board layout.
*/

string Board::getLayout()
{
	return _layout;																		//returning the layout
}

/*
This method returns the current color.
Input: None.
Output: The current color.
*/

int Board::getCurrColor()
{
	return _currColor;																	//returninh the current color
}

/*
This method returns the white game pieces array.
Input: None.
Output: The white game pieces array.
*/

GamePiece** Board::getWhite()
{
	return _player1;																	//returning the white pieces array
}

/*
This method returns the black game pieces array.
Input: None.
Output: The black game pieces array.
*/

GamePiece** Board::getBlack()
{
	return _player2;																	//returning the black pieces array
}

/*method will return the index of the last pawn to double step
* input: none 
* output: the index of the last pawn to double step
*/

int Board::getLastPawnToDoubleStep()
{
	return _lastPawnToDoubleStep;														//returning the index
}

/*method will return if the last turn was a pawn double step
* input: none
* output: if the last turn was a pawn double step (1  or 0)
*/

int Board::getIsLastTurnWasDoubleStep()
{
	return _isLastTurnWasDoubleStep;													//returning the flag
}

/*
This method sets a new current color.
Input: A new color.
Output: None.
*/

void Board::setColor(const int color)
{
	_currColor = color;																	//setting the colot to the given one
}

/*
This method sets a new char to a specific location in the layout.
Input: An index and a game piece (represented in char).
Output: None.
*/

void Board::setLayout(int index, char piece)
{
	_layout[index] = piece;																//setting layout[index] to the given char
}

/*
* method will set the _lastPawnToDoubleStep field
* to the givem value
* input: the new value
* output: none
*/

void Board::setLastPawnToDoubleStep(int index)
{
	_lastPawnToDoubleStep = index;														//setting _lastPawnToDoubleStep to the given value													
}

/*
* method will set the _isLastTurnWasDoubleStep field
* to the givem value
* input: the new value
* output: none
*/

void Board::setIsLastTurnWasDoubleStep(int newVal)
{
	_isLastTurnWasDoubleStep = newVal;													//setting _isLastTurnWasDoubleStep to the given value
}

/*
This method sets the 'eaten' status for a game piece.
Input: The piece's color, index and new 'eaten' status.
Output: None.
*/

void Board::setIsEaten(int color, int index, int newVal)
{
	if (!color)																			//for black
	{
		_player2[index]->setEaten(newVal);												//setting the piece to be eaten
	}
	else																				//for white
	{
		_player1[index]->setEaten(newVal);												//setting the piece to be eaten
	}
}

/*
This method checks if a game piece has been eaten.
Input: The current board layout, the destination string, the destination col, the destination row and the opponnent game pieces array.
Output: The updated opponent's game pieces array.
*/

GamePiece** Board::checkIfEaten(string layout, string dst, int dstCol, int dstRow, GamePiece** opponent)
{
	int i = 0;

	if (_layout[(dstCol + dstRow) - 1] != EMPTY_SPOT)									//if the dst of the turn was not empty
	{
		for (i = 0; i < NUM_OF_PIECES_PER_COLOR; i++)									//searching for the eaten piece
		{
			if (dst == opponent[i]->getLocation())										//if we found the eaten piece 
			{
				setIsEaten(_currColor, i, 1);											//setting the piece to be eaten
				opponent[i]->setEaten(1);
				break;																	//breaking from the loop
			}
		}
	}
	
	return opponent;																	//returning the updated array
}

/*
This function prints the current board layout.
Input: None.
Output: None.
*/

void Board::printBoard()
{
	int i = 0 , k = 8, j = 0;

	for (i = k - 1; i >= 0; i--)														//printing the board currectly
	{
		for (j = 0; j < k; j++)								
		{
			cout << _layout[(i * k) + j] << "  ";
		}

		cout << endl;																	//new line
	}
}
