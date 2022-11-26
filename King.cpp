#include "King.h"

/*
This method is c'tor for the king.
Input: the starting location
Output: None.
*/

King::King(std::string location) : GamePiece(location)				//using gamepiece c'tor
{
}

/*
This method checks if the king's move is valid.
Input: A new location and the current board layout.
Output: If the move is valid or not.
*/

int King::checkMoveType(string newLocation, string layout)
{
	int isValid = 0;
																	//check for horizontal and vertical movement
	if (((abs(_location[ROW] - newLocation[3]) == 1 || abs(_location[COL] - newLocation[2]) == 1) && (_location[ROW] == newLocation[3] || _location[COL] == newLocation[2])))
	{
		isValid = 1;
	}																//check for diagonale movement
	else if ((abs(_location[ROW] - newLocation[3]) == 1 && abs(_location[COL] - newLocation[2]) == 1) && (_location[COL] + 1 == newLocation[2] || _location[COL] - 1 == newLocation[2]))
	{
		isValid = 1;
	}

	return isValid;													//returning the result
}

/*
This method checks if the king has done a check.
Input: The king opponent king , and the current board layout.
Output : If there is a check.
*/

int King::isCheck(GamePiece* king, string layout)
{
	return checkMoveType("  " + king->getLocation(), layout);		//calling check move type , but with the opponent king location as destanetion
}	

int King::isEnPassat(string dst, string layout, int dstCol, int dstRow, int isDoubleLasTurn, string lastPawnToDoubleStep)
{
	return 0;														//returning 0 (implementation only for pawn , other pieces return 0)
}

/*
This method moves the king to its new location.
Input: A new location on the board.
Output: None.
*/

void King::move(string newLocation)
{
	_location[COL] = newLocation[2];								//setting the new colom
	_location[ROW] = newLocation[3];								//setting the row
}