#include "Menu.h"
/// <summary>
/// Constructor of menu class
/// </summary>
/// <param name="width">Width of menu in px</param>
/// <param name="height">Height of menu in px</param>
/// <param name="numberOfOptions">Number of option in menu</param>
/// <param name="text">Text of options in menu</param>
Menu::Menu(float width, float height,int numberOfOptions, const std::string *text)
{
	this->height = height;
	this->width = width;
	this->numberOfOptions = numberOfOptions;
	menu.resize(numberOfOptions);
	if (!font.loadFromFile(constants::fontFile))
	{
		exit(-4);
	}
	for (int i = 0; i < numberOfOptions; i++)
	{
		menu[i].setFont(font);
		menu[i].setFillColor(sf::Color::White);
		menu[i].setPosition(width / 4, height / numberOfOptions * i + height / numberOfOptions / 4);
		menu[i].setString(text[i]);
		menu[i].setCharacterSize(constants::SizeOfSquare/6*5);
	}
}

Menu::~Menu()
{
}
/// <summary>
/// Method to draw method
/// </summary>
/// <param name="window">Render window</param>
void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < numberOfOptions; i++)
	{
		window.draw(menu[i]);
	}
}
/// <summary>
/// Method to get option with position of cursor
/// </summary>
/// <param name="posX">X of cursor positon</param>
/// <param name="posY">Y of cursor positon</param>
/// <returns>Return number of option</returns>
int Menu::choose(int posX, int posY)
{
	if (posX >= (constants::widthBlocks * constants::SizeOfSquare + constants::borderThickness) || posY >= (constants::heightBlocks / 2 * constants::SizeOfSquare) || posX < 0 || posY < 0)
	{
		return -1;
	}
	for (int i = numberOfOptions - 1; i >=0; i--)
	{
		if (menu[i].getPosition().y - height / numberOfOptions / 4 <= posY)
			return i;
	}
	return -2;
}