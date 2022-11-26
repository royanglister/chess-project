#pragma once

#include <string>
#include "GamePiece.h"

class King : public GamePiece
{
public:
	//c'tor
	King(std::string location);
	
	//pure virtual methods
	virtual int isEnPassat(string dst, string layout, int dstCol, int dstRow, int isDoubleLasTurn, string lastPawnToDoubleStep);
	virtual int checkMoveType(string newLocation, string layout);
	virtual int isCheck(GamePiece* king, std::string layout);
	virtual void move(std::string newLocation);
};