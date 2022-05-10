#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Cell.h"
class Field
{

public:
	Field(int heightBlocks, int withBlocks, int height, double delay, int offsetX, int offsetY);
	~Field();
	int update();
	
	int Get_posForSpawnX();
	int Get_posForSpawnY();
	int getHeightBlocks();
	int getWidthBlocks();
	int Get_height();
	int GetElemField(int x, int y);
	void SetElemField(int x, int y, int val);
	void SetDelay(double delay);
	double GetDelay();
	void ResetDelay();
	void draw(sf::RenderWindow& window, Cell cell);
	int GetOffsetX();
	int GetOffsetY();
	void clearField();
	void SetDefaultDelay(double delay);
	bool isOver();
	void setDynamicDelay();
	void updateDynamicDelay(double time);
	int GetUps(int x);
	Field& operator=(const Field& t);
private:
	double getDynamicDelay(double time);
	double delay, defaultDelay;
	bool isDelayDynamic;
	int heightBlocks, widthBlocks, posForSpawnX, posForSpawnY, height, offsetX, offsetY;
	std::vector<std::vector<int>> field;
	std::vector<int> ups;
};

