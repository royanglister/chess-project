#include "Queen.h"

/*
This method is c'tor for the queen.
Input: the starting location
Output: None.
*/

Queen::Queen(std::string location) : GamePiece(location), Rook(location), Bishop(location)
{
}

/*
This method checks if the queen's move is valid.
Input: A new location and the current board layout.
Output: If the move is valid or not.
*/

int Queen::checkMoveType(string newLocation, string layout)
{																//using rook and bishop checkmovetype 
	return Rook::checkMoveType(newLocation, layout) || Bishop::checkMoveType(newLocation, layout);
}

/*
This method checks if the queen has done a check.
Input: The opponent king and the current board layout.
Output: If there is a check.
*/

int Queen::isCheck(GamePiece* king, string layout)
{																//using rook and bishop is check 
	return Rook::isCheck(king, layout) || Bishop::isCheck(king, layout);
}

int Queen::isEnPassat(string dst, string layout, int dstCol, int dstRow, int isDoubleLasTurn, string lastPawnToDoubleStep)
{
	return 0;													//returning 0 (implementation only for pawn , other pieces return 0)
}

/*
This method moves the queen to its new location.
Input: A new location on the board.
Output: None.
*/

void Queen::move(std::string newLocation)
{
	_location[COL] = newLocation[2];							//setting the new colom
	_location[ROW] = newLocation[3];							//setting the new row
}