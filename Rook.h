#pragma once
#include "GamePiece.h"

class GamePiece;
class Rook : virtual public GamePiece
{
	public:
		//c'tor
		Rook(string location);

		//pure virtual methods
		virtual int isEnPassat(string dst, string layout, int dstCol, int dstRow, int isDoubleLasTurn, string lastPawnToDoubleStep);
		virtual int checkMoveType(string newLocation, string layout);
		virtual int isCheck(GamePiece* king, string layout);
		virtual void move(string newLocation);
};

