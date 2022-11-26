#include "Pawn.h"
#include <iostream>
#include <string>

/*
This method is c'tor for the pawn.
Input: the starting location
Output: None.
*/

Pawn::Pawn(string location, int color) : GamePiece(location), _color(color)	//using gamepiece c'tor , and also initalizing the color field
{
}

/*
This method checks if the pawn's move is valid.
Input: A new location and the current board layout.
Output: If the move is valid or not.
*/

int Pawn::checkMoveType(string newLocation, string boardLayout)
{
	int isDoubleStep = 0, row = 1, isValid = 0, startLine = 7, offset = -8, currPawnLocation = ((int)_location[ROW] - 49) * 8 + (_location[COL] - 96);
	int dstLocation = ((int)newLocation[3] - 49) * 8 + (newLocation[2] - 96);

	if (_color)																//If the pawn color is black.
	{
		row = -1;															//changing the row
		startLine = 2;														//changing the  start line
		offset = 8;															//changing the offset
	}

	if (_location[COL] == newLocation[2])									//if the coloms of the dst and src are equale
	{																		//check for 1 square movement
		if ((_location[ROW] - newLocation[3] == row && (boardLayout[currPawnLocation + offset - 1]) == EMPTY_SPOT))
		{
			isValid = 1;
		}																	//check for 2 square movement
		else if ((_location[ROW] - newLocation[3] == row * 2 && (int)_location[ROW] - 48 == startLine) && (boardLayout[currPawnLocation + (offset * 2) - 1]) == EMPTY_SPOT)
		{
			isValid = 1;
			isDoubleStep = 1;												//lifting the double step flag
		}
	}
																			//trying to eat
	else if (abs(_location[COL] - newLocation[2]) == abs(row) && abs(_location[ROW] - newLocation[3]) == abs(row) && boardLayout[dstLocation - 1] != EMPTY_SPOT) 
	{
		if ((boardLayout[currPawnLocation] + offset - 1) != EMPTY_SPOT || (boardLayout[currPawnLocation] + offset + 1) != EMPTY_SPOT)
		{
			isValid = 1;
		}
	}

	if (isDoubleStep)														//if the pawn did a double step
	{
		isValid = 2;														//we set is valid to 2
	}

	return isValid;															//returning the result

}

/*
This method checks if the pawn has done a check.
Input: The opponent king and the current board layout.
Output: If there is a check.
*/

int Pawn::isCheck(GamePiece* king, string layout)
{
	int offset = -1, isValid = 0;

	if (_color)																//if the pawn color is black
	{
		offset = 1;															//we set offset to 1
	}
																			//checking if the king location is one of the 2 digonale eating spots of the pawn
	if ((_location[COL] - 1 == king->getLocation()[COL] && _location[ROW] + offset == king->getLocation()[ROW]) || (_location[COL] + 1 == king->getLocation()[COL] && _location[ROW] + offset == king->getLocation()[ROW]))
	{
		isValid = 1;
	}
	
	return isValid;															//returning the result
}

/*
* method will check if the pawn did en passent move
*input: the dst location, the board layout, the destenation row and colom,
*the flag for doublestep, and the location of the last pawn to double step
*output: if there was en passent (1 or 0)
*/

int Pawn::isEnPassat(string dst, string layout, int dstCol, int dstRow, int isDoubleLasTurn, string lastPawnToDoubleStep)
{
	char pawnSide = 'p';
	int startLine = 7, offset = -8, row = 1, i  = 0;						//declaring the variables
	string potencialPawn = dst;

	if (_color)																//if the pawn color is black
	{
		startLine = 2;														//setting start line to 2
		offset *= -1;														
		row = -1;
		pawnSide = 'P';														//setting pawnside to capital 'p'
	}

	potencialPawn[ROW] -= offset / 8;
	offset *= -1;
																			//checking if there is en passent
	if (abs(_location[COL] - dst[COL]) == abs(row) && abs(_location[ROW] - dst[ROW]) == abs(row) && layout[dstRow + dstCol + offset - 1] == pawnSide && layout[dstRow + dstCol - 1] == EMPTY_SPOT && lastPawnToDoubleStep == potencialPawn && isDoubleLasTurn) // Trying to eat with en passat
	{
		return offset;														//returning offset
	}

	return 0;																//returning 0
}

/*
This method moves the pawn to its new location.
Input: A new location on the board.
Output: None.
*/

void Pawn::move(string newLocation)
{
	_location[COL] = newLocation[2];										//setting the new colom 
	_location[ROW] = newLocation[3];										//setting the new row
}