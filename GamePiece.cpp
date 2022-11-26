#include "GamePiece.h"

/*
This method is a c'tor for a game piece.
Input: the starting location
Output: None.
*/

GamePiece::GamePiece(string location) : _location(location) , _isEaten(0)			//initializing the fields 
{

}

/*
This method is a d'tor for a game piece.
Input: None.
Output: None.
*/

GamePiece::~GamePiece()
{

}


/*
This method returns the 'eaten' status of a game piece.
Input: None.
Output: The 'eaten' status of a game piece.
*/

int GamePiece::getStatus()
{
	return _isEaten;																//returning the field value
}

/*
This method returns the current location of a game piece.
Input: None.
Output: The current location of a game piece.
*/

string GamePiece::getLocation()
{
	return _location;																//returning the piece location
}

/*
This method sets a new 'eaten' status for a game piece.
Input: The new 'eaten' status of the game piece.
Output: None.
*/

void GamePiece::setEaten(const int newValue)
{
	_isEaten = newValue;															//setting the "isEtean" field
}

/*
This method checks if the piece's move is valid and throws the according movement error codes.
Input: a pointer to the board and a new location on the board.
Output: If the piece's move is valid (the move code) , or thrown code (invalid move).
*/

int GamePiece::checkMovement(Board *board , string newLocation)
{
	int validMove = 0, i = 0, k = 0, moveCode = 0, offset = 0, isDouble = 0, srcCol = 0, srcRow = 0, dstCol = 0, dstRow = 0, color = 0, currPieceIndex = 0;
	int enPassentFlag = 0;
	char eatenPawn = 'p';
	string boardLayout = board->getLayout() , temp = "";
	string src = newLocation.substr(0 , 2) , dst = newLocation.substr(2 , 2);
	
	GamePiece* currKing;
	GamePiece* opponentKing;														//declaring the variales 
	GamePiece** opponent;
	GamePiece** currPlayer;

	srcRow = (((int)newLocation[1]) - 49) * 8;
	dstRow = (((int)newLocation[3]) - 49) * 8;										//converting the locations to numbers we can use them in the layout string
	srcCol = (int)newLocation[0] - 96;
	dstCol = (int)newLocation[2] - 96;

	if (src == dst)																	//if the src and dst squares are the same one
	{
		moveCode = 7;																//changing the move code to 7
		throw(moveCode);															//throwing the code
	}

	if (board->getIsLastTurnWasDoubleStep())
	{
		isDouble = 1;																//a helpaer variable in case of a self check that was coused by en passent move
	}

	if (boardLayout[(srcCol + srcRow) - 1] != EMPTY_SPOT)							//checking if source the spot is empty
	{
		if (board->getCurrColor())													//if the current color is black
		{																			//checking if the source square contains a black piece
			if (boardLayout[(srcCol + srcRow) - 1] >= BIG_A && boardLayout[(srcCol + srcRow) - 1] <= BIG_Z)
			{
				moveCode = 2;														//if not , we set the move code to 2
				throw(moveCode);													//and throw it
			}
		}
		else																		//if the current color is white
		{																			//checking if the source square contains a white piece
			if (boardLayout[(srcCol + srcRow) - 1] >= SMALL_A && boardLayout[(srcCol + srcRow) - 1] <= SMALL_Z)
			{
				moveCode = 2;														//if not , we set the move code to 2
				throw(moveCode);													//and throw it
			}
		}
	}
	else																			//if the source square is empty
	{
		moveCode = 2;																//we set the move code to 2
		throw(moveCode);															//and throw it
	}

	if (board->getCurrColor())														//if the current color is black
	{																				//if the destanetion contians a black piece 
		if (boardLayout[(dstCol + dstRow) - 1] >= SMALL_A && boardLayout[(dstCol + dstRow) - 1] <= SMALL_Z)
		{
			moveCode = 3;															//we set the move code to 3
			throw(moveCode);														//and throw it
		}
	}
	else																			//for white
	{																				//if the destanetion contians a white piece 
		if (boardLayout[(dstCol + dstRow) - 1] >= BIG_A && boardLayout[(dstCol + dstRow) - 1] <= BIG_Z)
		{
			moveCode = 3;															//we set the move code to 3
			throw(moveCode);														//and throw it
		}
	}

	if (board->getCurrColor())														//the current player is black
	{
		opponent = board->getWhite();												//opponent is white
		currPlayer = board->getBlack();												//current player is black
		color = 1;
		eatenPawn = 'P';
	}
	else																			//for white
	{
		opponent = board->getBlack();												//opponent is black
		currPlayer = board->getWhite();												//current player is white
	}

	currKing = currPlayer[4];														//getting the two kings (opponent and current kings)
	opponentKing = opponent[4];
	
	for (i = 0; i < NUM_OF_PIECES_PER_COLOR; i++)							
	{
		if (src == currPlayer[i]->getLocation())									//searching for the moved piece 
		{
			if (currPlayer[i]->_isEaten)											//if the piece is eaten 
			{
				moveCode = 2;
				throw(moveCode);													//we throe move code 2
			}
																					//if the moved piece is a pawn , we check for an en passent
			if (boardLayout[srcCol + srcRow - 1] == 'P' || boardLayout[srcCol + srcRow - 1] == 'p')
			{
				offset = currPlayer[i]->isEnPassat(dst, boardLayout, dstCol , dstRow, isDouble , opponent[board->getLastPawnToDoubleStep()]->getLocation());

				if (offset)															//if there was en passent move
				{
					enPassentFlag = 1;												//lifting the en passent flag
					dst[ROW] += offset / 8;											//offsetting the dst, and checking for eaten pieces
					opponent = board->checkIfEaten(boardLayout, dst, dstCol, dstRow + offset, opponent);
					board->setLayout(dstCol + dstRow + offset - 1, EMPTY_SPOT);		//updting the board layout
					validMove = 10;													//setting the move code to 10

					temp = currPlayer[i]->getLocation();							//saving the current location of the pawn , and his index ,in case that the action will cocuse self check
					currPlayer[i]->move(newLocation);								//moving the pawn
					currPieceIndex = i;												//saving the pawn index
																					//updating the board layout
					board->setLayout((dstCol + dstRow - 1), boardLayout[srcCol + srcRow - 1]);
					board->setLayout((srcCol + srcRow - 1), EMPTY_SPOT);
					break;															//breaking from the loop
				}
			}
			
			if (!currPlayer[i]->checkMoveType(newLocation, boardLayout))			//checking if the move type is valid
			{
				moveCode = 6;
				throw(moveCode);													//if not , we throw code 6 
			}
			else if (currPlayer[i]->checkMoveType(newLocation, boardLayout) == 2)	//if a pawn did a double step
			{
				board->setLastPawnToDoubleStep(i);									//updating the index
				board->setIsLastTurnWasDoubleStep(1);								//lifting the double step flag
			}
			else 
			{
				board->setIsLastTurnWasDoubleStep(0);								//turning down the double stap flag , and checking for eaten pieces
				opponent = board->checkIfEaten(boardLayout, dst, dstCol, dstRow, opponent);
			}

			temp = currPlayer[i]->getLocation();									//saving the current location of the piece and its index ,in case that the action will cocuse self check
			currPlayer[i]->move(newLocation);										//moveing the piece 
			currPieceIndex = i;														//savong the index
																					//updatng the board layout
			board->setLayout((dstCol + dstRow - 1), boardLayout[srcCol + srcRow - 1]);
			board->setLayout((srcCol + srcRow - 1), EMPTY_SPOT);
			boardLayout = board->getLayout();
			break;																	//breaking from the loop
		}
	}

	for (i = 0; i < NUM_OF_PIECES_PER_COLOR; i++)									//loop for checking if the move coused self check
	{																				//if there is a check on the current player
		if (!opponent[i]->getStatus() && opponent[i]->isCheck(currKing, board->getLayout()))
		{
			if (enPassentFlag)														//if there was en passent
			{
				dstRow += offset;
				board->setLayout((dstCol + dstRow - 1), eatenPawn);					//updating the board (returning the eaten aeten pawn)
				boardLayout = board->getLayout();
				dstRow -= offset;
			}

			currPlayer[currPieceIndex]->move("  " + temp);							//moveing the piece back
																					//returnong the board to its state before the move
			board->setLayout((srcCol + srcRow - 1), boardLayout[dstCol + dstRow - 1]);
			board->setLayout((dstCol + dstRow - 1), EMPTY_SPOT);
			boardLayout = board->getLayout();

			if (isDouble)															//if there was a double step last turn
			{
				board->setIsLastTurnWasDoubleStep(1);								//we lift the flag back
			}
			else
			{
				board->setIsLastTurnWasDoubleStep(0);								//turning the flag down
			}

			moveCode = 4;
			throw(moveCode);														//throwing move code 4
		}
	}
																					//if we got here it means that the move is valid , and there is no self check
	if (board->getCurrColor())														//if the current color is black
	{
		board->setColor(0);															//we change the color to white (0) 
	}
	else																			//if the current color is white
	{
		board->setColor(1);															//we change the color to black (1) 
	}

	for (i = 0; i < NUM_OF_PIECES_PER_COLOR; i++)									//loop for cheking if there was check on the oher player
	{																				//if there is a check
		if (!currPlayer[i]->getStatus() && currPlayer[i]->isCheck(opponentKing, board->getLayout()))
		{
			validMove = 1;															//we set valid move to 1
			break;
		}
	}

	return validMove;																//returning valid move
}


