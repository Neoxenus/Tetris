#include "Menu.h"

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

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < numberOfOptions; i++)
	{
		window.draw(menu[i]);
	}
}

int Menu::choose(int posX, int posY)
{
	if (posX >= (constants::N * constants::SizeOfSquare + constants::borderThickness) || posY >= (constants::M / 2 * constants::SizeOfSquare) || posX < 0 || posY < 0)
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