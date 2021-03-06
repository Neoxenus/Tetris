#include "Cell.h"
/// <summary>
/// Constructor wich initilazed some variables
/// </summary>
Cell::Cell()
{
	this->posX = 0;
	this->posY = 0;
	this->color = 0;
	this->offsetX = 0;
	this->offsetY = 0;
}

Cell::~Cell()
{
}

sf::Color Cell::GetColorRGB(int TypeOfColor)
{
	if (TypeOfColor < 1 || TypeOfColor > 7)
	{
		//std::cerr << "Incorrect argument int TypeOfColor in function sf::Color Color::GetColor(int)\n";
		exit(-2);
	}
	sf::Color ans(constants::rgb[TypeOfColor - 1][0], constants::rgb[TypeOfColor - 1][1], constants::rgb[TypeOfColor - 1][2]);
	return ans;
}
/// <summary>
/// Method wich set position and color of cell to draw
/// </summary>
/// <param name="posX">X coordinate of position</param>
/// <param name="posY">Y coordinate of position</param>
/// <param name="offsetX">X of offset</param>
/// <param name="offsetY">Y of offset</param>
/// <param name="color">Color of cell</param>
void Cell::setCell(int posX, int posY, int offsetX, int offsetY, int color)
{
	this->posX = posX;
	this->posY = posY;
	this->color = color;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
}
/// <summary>
/// Method wich draw one square in the field
/// </summary>
/// <param name="window">Render window in which we want draw cell</param>
void Cell::draw(sf::RenderWindow& window)
{
	sf::RectangleShape square(sf::Vector2f(constants::SizeOfSquare - constants::CellOutlines, constants::SizeOfSquare - constants::CellOutlines));
	square.setFillColor(this->GetColorRGB(color));
	square.setPosition((float)posX * constants::SizeOfSquare, (float)posY * constants::SizeOfSquare);
	square.move(sf::Vector2f((float)offsetX, (float)offsetY));
	square.move(constants::borderThickness, constants::borderThickness);
	window.draw(square);
}
