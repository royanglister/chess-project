#include "Bishop.h"

/*
This method is a c'tor for the bishop.
Input: the starting location
Output: None.
*/

Bishop::Bishop(string location) : GamePiece(location)
{

}

/*
This method checks if the bishop's move is valid.
Input: A new location and the current board layout.
Output: If the move is valid or not.
*/

int Bishop::checkMoveType(string newLocation, string layout)
{
	int i = 0 , colOffset = -1, rowOffset = 1, isValid = 1, temp = 0;
	int srcRow = 0, srcCol = 0;
	int dstRow = 0, dstCol = 0;

	srcRow = (((int)_location[ROW]) - 49);									//initializing coordinates
	dstRow = (((int)newLocation[3]) - 49);
	srcCol = (int)_location[COL] - 96;
	dstCol = (int)newLocation[2] - 96;

	temp = (srcRow + 1) * 8;												//for movement up

	if (srcRow - dstRow > 0)												//for movement down
	{
		colOffset = 1;
		rowOffset = -1;														//row offset is -1 because we moveing down
		temp = (srcRow - 1) * 8;											//temp show us the current place we check on the board
	}

																			//if the given dst is valid
	if (srcRow + srcCol == dstRow + dstCol || srcRow - srcCol == dstRow - dstCol)									
	{
		if (srcRow - srcCol == dstRow - dstCol)
		{
			colOffset *= -1;
		}

		for (i = 1; i < abs(dstRow - srcRow); i ++)							//checking the difference in rows
		{
			srcCol += colOffset;											//moveing the colom 

			if (layout[temp + srcCol - 1] != EMPTY_SPOT)					//if the spot is not empty
			{
				isValid = 0;												//the move is not valid
			}
			
			temp += rowOffset * 8;											//moveing to the next row 
		}
	}
	else																	//if the given dst is not valid
	{
		isValid = 0;
	}

	return isValid;															//returning the result
}

/*
This method checks if the bishop has done a check.
Input: The opponent's king ,and the current board layout.
Output: If there is a check.
*/

int Bishop::isCheck(GamePiece* king, string layout)
{
	return Bishop::checkMoveType("  " + king->getLocation(), layout);		//calling checkMoveType, but with the opponent's king location as the dst
}

int Bishop::isEnPassat(string dst, string layout, int dstCol, int dstRow, int isDoubleLasTurn, string lastPawnToDoubleStep)
{
	return 0;																//function only for pawn to do somethong	
}

/*
This method moves the bishop to its new location.
Input: A new location on the board.
Output: None.
*/

void Bishop::move(string newLocation)
{
	_location[COL] = newLocation[2];										//setting the new colom
	_location[ROW] = newLocation[3];										//detting the new row
}