#include "moveExceptions.h"

/*
This method retirns a proper error message according to the movement error code given.
Input: The error code.
Output: The error message.
*/

string moveExceptions::what(int errorCode)
{
	switch (errorCode)
	{
	case 2:
		return "ERROR: src does not contain a piece of the current color\n";
	case 3:
		return "ERROR: dst contains a piece of the current color\n";
	case 4:
		return "ERROR: this action wil couse check on the current color\n";
	case 5:
		return "ERROR: invalid src or dst indexes\n";
	case 6:
		return "ERROR: invalid piece movement\n";
	case 7:
		return "ERROR: src and dst are the same place\n";
	default:
		break;
	}
}
