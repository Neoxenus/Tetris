#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
class Field
{

public:
	Field(int heightBlocks, int widthBlocks, int height, double delay, int offsetX, int offsetY);
	~Field();

	////show wich methods use anothe objects////
	//bot+main
	int update();
	//tetro
	int Get_posForSpawnX();
	int Get_posForSpawnY();

	//tetro+bot
	int getHeightBlocks();
	int getWidthBlocks();
	//tetro+bot
	int GetElemField(int x, int y);
	//tetrp
	void SetElemField(int x, int y, int val);

	void draw(sf::RenderWindow& window, Cell cell);
	//tetro
	int GetOffsetX();
	int GetOffsetY();

	//main
	void clearField();
	void SetDefaultDelay(double delay);
	bool isOver();
	void setDynamicDelay();
	void updateDynamicDelay(double time);
	void SetDelay(double delay);

	void ResetDelay();
	double GetDelay();

	//bot
	int GetUps(int x);

	Field& operator=(const Field& t);
private:
	double delay, defaultDelay;
	bool isDelayDynamic;
	int heightBlocks, widthBlocks, posForSpawnX, posForSpawnY, height, offsetX, offsetY;
	std::vector<std::vector<int>> field;
	std::vector<int> ups;


	int Get_height();
	double getDynamicDelay(double time);

};

