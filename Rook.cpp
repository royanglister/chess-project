#include "Rook.h"
/*
This method is c'tor for the rook.
Input: the starting location
Output: None.
*/

Rook::Rook(string location) : GamePiece(location)					//using gamepiece c'tor
{
}

/*
This method checks if the rook's move is valid.
Input: A new location and the current board layout.
Output: If the move is valid or not.
*/

int Rook::checkMoveType(string newLocation, string layout)
{
	int temp = 0, isValid = 1, offset = 1, i = 0;
	int srcRow = 0, srcCol = 0;										//declaring the variables
	int dstRow = 0, dstCol = 0;

	srcRow = (((int)_location[ROW]) - 49);
	dstRow = (((int)newLocation[3]) - 49);							//converting the locations to numbers we can use them in the layout string
	srcCol = (int)_location[COL] - 96;
	dstCol = (int)newLocation[2] - 96;

	temp = (srcRow + 1) * 8;										//we "assume" that the movment is up

	if (dstRow - srcRow < 0)										//if the movement is down
	{
		offset = -1;												//setting offset to -1
		temp = (srcRow - 1) * 8;									//setting temp to the row below the rook 
	}
	else if (dstCol - srcCol < 0)									//if the movement is left
	{
		offset = -1;												//setting offset to -1
		temp = srcRow * 8;											//setting temp to the row of the took
	}
	else if (dstCol - srcCol > 0)									//if the movement is right
	{
		temp = srcRow * 8;											//setting temp to the row of the took
	}
																	//checking the movement type
	if (_location[COL] == newLocation[2])							//for vertical movement
	{
		for (i = 1;i < abs(dstRow - srcRow) && isValid; i ++)		//checking the difference in the rows
		{
			if (layout[temp + srcCol - 1] != EMPTY_SPOT)			//if the path to the destanation isnt clear
			{
				isValid = 0;										//the movement is not valid
			}

			temp += offset * 8;										//moveing to the bext row
		}
	}
	else if (_location[ROW] == newLocation[3])						//for hrizontal movement	
	{
		for (i = 1; i < abs(dstCol - srcCol) && isValid; i ++)		//checking the difference in the coloms
		{
			temp += offset;											//moving to the next colom 

			if (layout[temp + srcCol - 1] != EMPTY_SPOT)			//if the path to the destanation isnt clear
			{
				isValid = 0;										//the movement is not valid
			}
		}
	}
	else
	{
		isValid = 0;
	}

	return isValid;													//returning the result
}

/*
This method checks if the rook has done a check.
Input: The opponent king and the current board layout.
Output: If there is a check.
*/

int Rook::isCheck(GamePiece* king, string layout)
{																	//calling check move type , but with the opponent king location as destanetion
	return Rook::checkMoveType("  " + king->getLocation(), layout);
}

int Rook::isEnPassat(string dst, string layout, int dstCol, int dstRow, int isDoubleLasTurn, string lastPawnToDoubleStep)
{
	return 0;														//returning 0 (implementation only for pawn , other pieces return 0)
}

/*
This function moves the rook to its new location.
Input: A new location on the board.
Output: None.
*/

void Rook::move(string newLocation)
{
	_location[COL] = newLocation[2];								//setting the new colom
	_location[ROW] = newLocation[3];								//setting the new row
}