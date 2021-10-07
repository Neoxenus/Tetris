#pragma once
#include "Field.h"
#include "Tetromino.h"
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

