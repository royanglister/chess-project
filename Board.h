#pragma once
#include "GamePiece.h"

using std::cout;
using std::endl;
using std::string;

#define NUM_OF_PIECES_PER_COLOR 16
#define LINE_LENGTH 8

class GamePiece;
class Board
{
private:
	int _currColor;
	int _lastPawnToDoubleStep;
	int _isLastTurnWasDoubleStep;
	std::string _layout;

	GamePiece** _player1;
	GamePiece** _player2;

public:
	//c'tor and d'tor
	Board();
	~Board();

	//getters
	std::string getLayout();
	int getCurrColor();
	int getLastPawnToDoubleStep();
	int getIsLastTurnWasDoubleStep();
	GamePiece** getWhite();
	GamePiece** getBlack();

	//setters
	void setColor(const int color);
	void setLayout(int index, char piece);
	void setLastPawnToDoubleStep(int index);
	void setIsLastTurnWasDoubleStep(int newVal);
	void setIsEaten(int color, int index, int newVal);

	GamePiece** checkIfEaten(string layout, string dst, int dstCol, int dstRow, GamePiece** opponent);

	void printBoard();
};

