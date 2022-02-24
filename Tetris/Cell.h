#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"
class Cell
{
public:
	Cell();
	~Cell();
	
	void setCell(int posX, int posY, int offsetX, int offsetY, int color);
	void draw(sf::RenderWindow &window);
private:
	sf::Color GetColorRGB(int TypeOfColor);

	int posX, posY, offsetX, offsetY, color;
};