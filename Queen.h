#pragma once
#include "Board.h"
#include "Bishop.h"
#include "Rook.h"

class Queen : public Rook , public Bishop //inharits from rook and bishop insted of gamepiece
{
	public:
		//c'tor
		Queen(string location);

		//pure virtual methods
		virtual int isEnPassat(string dst, string layout, int dstCol, int dstRow, int isDoubleLasTurn, string lastPawnToDoubleStep);
		virtual int checkMoveType(string newLocation, string layout);
		virtual int isCheck(GamePiece* king, string layout);
		virtual void move(string newLocation);
};

