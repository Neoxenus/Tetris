#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"
class Cell
{
public:
	Cell();
	~Cell();
	sf::Color GetColorRGB(int TypeOfColor);
	void setCell(int posX, int posY, int offsetX, int offsetY, int color);
	void draw(sf::RenderWindow &window);
private:
	int posX, posY, offsetX, offsetY, color;
};