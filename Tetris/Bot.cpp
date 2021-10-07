#include "Bot.h"

Bot::Bot()
{
	rotate = 0;
	dx = 0;
}

Bot::~Bot()
{
}

void Bot::analysis(Tetromino cur, Tetromino next, Field A)
{
	//std::cout << "\nanalysis iteration\n";
	Tetromino tmpDef = cur;
	Field Ftmp = A;
	int numOfRotate = 0, tmp_dx = 0, numOfGaps = 0;
	int result, numOfPillars, bestState = constants::BestState + 1, tmpState, weight;
//	int minWeight = 4 * Ftmp.Get_M() + 1, minNumOfGaps = 5, theBestResult = -1, minNumOfPillars = Ftmp.Get_N() + 1;
	for (int i = 0; i < 4; i++)
	{
			for (int j = -6; j <= 6; j++)
			{
				Tetromino tmp = tmpDef;
				if (!tmp.horizontalMoving(Ftmp, j))
					continue;
				while (!tmp.falling(Ftmp)) {}
				result = this->GetResult(Ftmp);
				if (result == constants::isOver)
				{
					Ftmp = A;
					continue;
				}
				weight = this->GetWeightOfTetromino(tmp, Ftmp);
				numOfGaps = this->GetNumOfGaps(tmp, Ftmp);
				numOfPillars = this->GetNumOfPillars(Ftmp);
				tmpState = this->evaluation_function(result, numOfPillars, weight, numOfGaps) + analysis(next, Ftmp);
				Ftmp = A;
				if (bestState > tmpState)
				{
					bestState = tmpState;
					//theBestResult = result;
					//minNumOfGaps = numOfGaps;
					//minNumOfPillars = numOfPillars;
					//minWeight = weight;
					numOfRotate = i;
					tmp_dx = j ;
				}
				//std::cout << "Result: " << result << " Pillars: " << numOfPillars << " Weight: " << weight << " Gaps: " << numOfGaps <<
				//	"\t  ||||\t" << "Result: " << theBestResult << " Pillars: " << minNumOfPillars << " Weight: " << minWeight << " Gaps: " << minNumOfGaps << std::endl;
			}
		if ((tmpDef.GetType() == static_cast<int>(constants::TetrominoType::O)) ||
			(i > 0 && 
				(tmpDef.GetType() == static_cast<int>(constants::TetrominoType::I) ||
				tmpDef.GetType() == static_cast<int>(constants::TetrominoType::S)||
				tmpDef.GetType() == static_cast<int>(constants::TetrominoType::Z))))
			break;
		tmpDef.rotate(Ftmp);
	}
	this->dx = tmp_dx;
	this->rotate = numOfRotate;
}

int Bot::analysis(const Tetromino cur, const Field A)
{
	//std::cout << "\nanalysis iteration\n";
	Tetromino tmpDef = cur;
	Field Ftmp = A;
	int  numOfGaps = 0;
	int result, numOfPillars, bestState = constants::BestState, tmpState, weight;
	//	int minWeight = 4 * Ftmp.Get_M() + 1, minNumOfGaps = 5, theBestResult = -1, minNumOfPillars = Ftmp.Get_N() + 1;
	for (int i = 0; i < 4; i++)
	{
			for (int j = -6; j <= 6; j++)
			{
				Tetromino tmp = tmpDef;
				if (!tmp.horizontalMoving(Ftmp, j))
					continue;
				while (!tmp.falling(Ftmp)) {}
				result = this->GetResult(Ftmp);
				if (result == constants::isOver)
				{
					Ftmp = A;
					continue;
				}

				weight = this->GetWeightOfTetromino(tmp, Ftmp);
				numOfGaps = this->GetNumOfGaps(tmp, Ftmp);
				numOfPillars = this->GetNumOfPillars(Ftmp);
				
				Ftmp = A;
				tmpState = this->evaluation_function(result, numOfPillars, weight, numOfGaps);
				if  (bestState>tmpState)
				{
					bestState = tmpState;
					//theBestResult = result;
					//minNumOfGaps = numOfGaps;
					//minNumOfPillars = numOfPillars;
					//minWeight = weight;
					//numOfRotate = i;
					//tmp_dx = j*sign;
				}
				//std::cout << "Result: " << result << " Pillars: " << numOfPillars << " Weight: " << weight << " Gaps: " << numOfGaps <<
				//	"\t  ||||\t" << "Result: " << theBestResult << " Pillars: " << minNumOfPillars << " Weight: " << minWeight << " Gaps: " << minNumOfGaps << std::endl;
			}
		if ((tmpDef.GetType() == static_cast<int>(constants::TetrominoType::O)) || 
			(i > 0 && 
					(tmpDef.GetType() == static_cast<int>(constants::TetrominoType::I) || 
					tmpDef.GetType() == static_cast<int>(constants::TetrominoType::S) ||
					tmpDef.GetType() == static_cast<int>(constants::TetrominoType::Z))))
			break;
		tmpDef.rotate(Ftmp);
	}
	return bestState;
}

bool Bot::Get_isRotate()
{
	if (rotate > 0)
	{
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
		ans += (A.Get_M() - cur.Get_y(i));
	return ans;
}

int Bot::GetNumOfGaps(Tetromino tmp, Field Ftmp)
{
	int numOfGaps = 0;

	for (int q = 0; q < 4; q++)
	{
		if (tmp.Get_y(q) == (Ftmp.Get_M() - 1) || Ftmp.GetElemField(tmp.Get_y(q) + 1, tmp.Get_x(q)) != 0)
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
	for (int j = 0; j < Ftmp.Get_N(); j++)
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
	else if (x == (Ftmp.Get_N() - 1))
	{
		if (Ftmp.GetUps(x - 1) - (Ftmp.GetUps(x)) >= 3)
			return true;
	}
	else if (x > 0 && x < (Ftmp.Get_N() - 1))
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
