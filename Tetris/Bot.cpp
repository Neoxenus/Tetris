#include "Bot.h"

Bot::Bot()
{
	rotate = 0;
	dx = 0;
}

Bot::~Bot()
{
}

void Bot::analysis(Tetromino cur, Tetromino next, Field A){
	Field Ftmp(A);
	Tetromino tmp(Ftmp);
	int numOfRotate = 0, tmp_dx = 0, numOfGaps = 0;
	int result, numOfPillars, bestState = constants::BestState + 1, tmpState, weight;

	for (int i = 0; i < 4; ++i){
			for (int j = -6; j <= 6; ++j){
				tmp = cur;
				if (!tmp.horizontalMoving(j))
					continue;
				while (!tmp.falling()) {}
				result = this->GetResult(Ftmp);
				if (result == constants::isOver){
					Ftmp = A;
					continue;
				}
				weight = this->GetWeightOfTetromino(tmp, Ftmp);
				numOfGaps = this->GetNumOfGaps(tmp, Ftmp);
				numOfPillars = this->GetNumOfPillars(Ftmp);
				tmpState = this->evaluation_function(result, numOfPillars, weight, numOfGaps) + analysis(next, Ftmp);
				Ftmp = A;
				if (bestState > tmpState){
					bestState = tmpState;
					numOfRotate = i;
					tmp_dx = j ;
				}
			}
		if ((cur.GetType() == static_cast<int>(constants::TetrominoType::O)) ||
			(i > 0 && 
				(cur.GetType() == static_cast<int>(constants::TetrominoType::I) ||
				cur.GetType() == static_cast<int>(constants::TetrominoType::S)||
				cur.GetType() == static_cast<int>(constants::TetrominoType::Z))))
			break;
		cur.rotate();
	}
	this->dx = tmp_dx;
	this->rotate = numOfRotate;
}

int Bot::analysis(const Tetromino cur, Field A){
	Field Ftmp(A);
	Tetromino tmpDef(A), tmp(Ftmp);
	tmpDef = cur;
	int  numOfGaps = 0;
	int result, numOfPillars, bestState = constants::BestState, tmpState, weight;
	for (int i = 0; i < 4; ++i){
			for (int j = -6; j <= 6; ++j){
				tmp = tmpDef;
				if (!tmp.horizontalMoving(j))
					continue;
				while (!tmp.falling()) {}
				result = this->GetResult(Ftmp);
				if (result == constants::isOver){
					Ftmp = A;
					continue;
				}
				weight = this->GetWeightOfTetromino(tmp, Ftmp);
				numOfGaps = this->GetNumOfGaps(tmp, Ftmp);
				numOfPillars = this->GetNumOfPillars(Ftmp);
				Ftmp = A;
				tmpState = this->evaluation_function(result, numOfPillars, weight, numOfGaps);
				if  (bestState>tmpState)		
					bestState = tmpState;
			}
		if ((tmpDef.GetType() == static_cast<int>(constants::TetrominoType::O)) || 
			(i > 0 && 
					(tmpDef.GetType() == static_cast<int>(constants::TetrominoType::I) || 
					tmpDef.GetType() == static_cast<int>(constants::TetrominoType::S) ||
					tmpDef.GetType() == static_cast<int>(constants::TetrominoType::Z))))
			break;
		tmpDef.rotate();
	}
	return bestState;
}

bool Bot::Get_isRotate()
{
	if (rotate > 0){
		rotate--;
		return true;
	}
	return false;
}


int Bot::Get_dx()
{
	if (dx > 0)
	{
		dx--;
		return 1;
	}
	if (dx < 0)
	{
		dx++;
		return -1;
	}
	return 0;
}

bool Bot::readyToFall()
{
	if (rotate == 0 && dx == 0)
		return true;
	return false;
}

int Bot::GetWeightOfTetromino(Tetromino cur, Field A)
{
	int ans=0;
	for (int i = 0; i < 4; i++)
		ans += (A.getHeightBlocks() - cur.Get_y(i));
	return ans;
}

int Bot::GetNumOfGaps(Tetromino tmp, Field Ftmp)
{
	int numOfGaps = 0;

	for (int q = 0; q < 4; q++)
	{
		if (tmp.Get_y(q) == (Ftmp.getHeightBlocks() - 1) || Ftmp.GetElemField(tmp.Get_y(q) + 1, tmp.Get_x(q)) != 0)
			continue;
		numOfGaps++;
	}
	return numOfGaps;
}

int Bot::GetResult(Field Ftmp)
{
	int result = Ftmp.update();
	if (Ftmp.isOver())
		result = constants::isOver;
	return result;
}

int Bot::GetNumOfPillars(Field Ftmp)
{
	int numOfPillars = 0;
	for (int j = 0; j < Ftmp.getWidthBlocks(); j++)
	{
		if (checkForPillars(Ftmp, j))
		{
			numOfPillars++;
			j++;
		}
	}
	return numOfPillars;
}

bool Bot::checkForPillars(Field Ftmp, int x)
{
	if (x == 0)
	{
		if (Ftmp.GetUps(x + 1) - (Ftmp.GetUps(x)) >= 3)
			return true;
	}	
	else if (x == (Ftmp.getWidthBlocks() - 1))
	{
		if (Ftmp.GetUps(x - 1) - (Ftmp.GetUps(x)) >= 3)
			return true;
	}
	else if (x > 0 && x < (Ftmp.getWidthBlocks() - 1))
	{
		if ((Ftmp.GetUps(x + 1) - (Ftmp.GetUps(x)) >= 3) && (Ftmp.GetUps(x - 1) - (Ftmp.GetUps(x)) >= 3))
			return true;
	}	
	return false;
}

int Bot::evaluation_function(int result, int pillars, int weight, int gaps)
{
	//double kr = 5, kp = 20, kw = 1, kg = 32;
	double kr = 10, kp = 100, kw = 20, kg = 400;
//	double kr = 10, kp = 120, kw = 20, kg = 400;

	int f;
	f = static_cast<int>(pillars * kp + weight * kw+ gaps * kg - kr * result);
	return f;
}
