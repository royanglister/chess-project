#include "Knight.h"

/*
This method is c'tor for the knight.
Input: the starting location of the knight
Output: None.
*/

Knight::Knight(string location) : GamePiece(location)		//using the gamepiece c'tor
{

}

/*
This method checks if the knight's move is valid.
Input: A new location and the current board layout.
Output: If the move is valid or not.
*/

int Knight::checkMoveType(string newLocation, string layout)
{
	int isValid = 0;
															//checking the difference (abs) between the dst and src rows and coloms 
	if ((abs(_location[ROW] - newLocation[3]) == 2 && abs(_location[COL] - newLocation[2]) == 1) || (abs(_location[ROW] - newLocation[3]) == 1 && abs(_location[COL] - newLocation[2]) == 2))
	{
		isValid = 1;										//its a valid move
	}

	return isValid;											//returning the result
}

/*
This method checks if the knight has done a check.
Input: The opponent king and the current board layout.
Output: If there is a check.
*/

int Knight::isCheck(GamePiece* king, string layout)
{															//calling check move type , but with the opponent king location as destanetion
	return checkMoveType("  " + king->getLocation(), layout);
}

int Knight::isEnPassat(string dst, string layout, int dstCol, int dstRow, int isDoubleLasTurn, string lastPawnToDoubleStep)
{
	return 0;												//returning 0 (implementation only for pawn , other pieces return 0)
}

/*
This method moves the knight to its new location.
Input: A new location on the board.
Output: None.
*/

void Knight::move(string newLocation)
{
	_location[COL] = newLocation[2];						//setting the new colom
	_location[ROW] = newLocation[3];						//setting the new row
}