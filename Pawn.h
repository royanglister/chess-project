#pragma once
#include "GamePiece.h"
#include <iostream>

class Pawn : public GamePiece
{
private:
	int _color;

public:
	// C'tor.
	Pawn(string location, int color); 

	//pure virtual methods
	virtual int isEnPassat(string dst, string layout, int dstCol, int dstRow, int isDoubleLasTurn, string lastPawnToDoubleStep);
	virtual int checkMoveType(string newLocation, string boardLayout);
	virtual int isCheck(GamePiece* king, string layout);
	virtual void move(string newLocation);

};

