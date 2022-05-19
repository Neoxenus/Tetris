#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
/// <summary>
/// Class to represent box to show statistic of game
/// </summary>
class StatisticBox
{
public:
	StatisticBox(float width, float height, int posX, int posY);
	~StatisticBox();
	void draw(sf::RenderWindow& window);
	void SetStatistics(long double value, int type);
	long double GetStatistics(int type);
private:
	long double values[constants::MAX_NUMBER_OF_STATISTICS_ITEMS];
	sf::Font font;
	sf::Text text[constants::MAX_NUMBER_OF_STATISTICS_ITEMS];
	float width, height;
	int posX, posY;
};
