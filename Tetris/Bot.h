#pragma once
#include "Field.h"
#include "Tetromino.h"
/// <summary>
/// Bot class used field and 2 tetromino to get the best position and values to contol them.
/// </summary>
class Bot
{
public:
	Bot();
	~Bot();
	void analysis(Tetromino cur, Tetromino next, Field A);
	bool Get_isRotate();
	int Get_dx();
	bool readyToFall();
private:
	int analysis(Tetromino cur, Field A);
	int GetWeightOfTetromino(Tetromino cur, Field A);
	int GetNumOfGaps(Tetromino cur, Field A);
	int GetResult(Field Ftmp);
	int GetNumOfPillars( Field Ftmp);
	bool checkForPillars(Field Ftmp, int x);
	int evaluation_function(int result, int pillars, int weight, int gaps);

	int rotate, dx;
	
};

