#pragma once

#include <iostream>
#include "Board.h"

using std::string;

#define ROW 1
#define COL 0

#define EMPTY_SPOT '#'
#define SMALL_A 'a'
#define SMALL_Z 'z'
#define BIG_A 'A'
#define BIG_Z 'Z'

class Board;
class GamePiece
{
protected:

	int _isEaten;
	string _location;

public:

	//c'tor and d'tor
	GamePiece(string location);
	~GamePiece();

	//getters
	int getStatus();
	string getLocation();

	//setter
	void setEaten(const int newValue);
	//static method to use in main funcion
	static int checkMovement(Board *board , string newLocation);

	//pure virtual methods
	virtual int isEnPassat(string dst, string layout, int dstCol, int dstRow, int isDoubleLasTurn, string lastPawnToDoubleStep) = 0;
	virtual int checkMoveType(string newLocation, string layout) = 0;
	virtual int isCheck(GamePiece* king, string layout) = 0;
	virtual void move(string newLocation) = 0;
};