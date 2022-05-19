#include "StatisticBox.h"
/// <summary>
/// Constructor to statistic box
/// </summary>
/// <param name="width">Width in px</param>
/// <param name="height">Height in px</param>
/// <param name="posX">X of position in px</param>
/// <param name="posY">Y of positon px</param>
StatisticBox::StatisticBox(float width, float height, int posX, int posY)
{
	this->width = width;
	this->height = height;
	this->posX = posX;
	this->posY = posY;
	if (!font.loadFromFile(constants::fontFile))
	{
		exit(4);
	}
	for (int i = 0; i < constants::MAX_NUMBER_OF_STATISTICS_ITEMS; i++)
	{
		values[i] = 0;
		text[i].setFont(font);
		text[i].setFillColor(sf::Color(160,160,160));
		text[i].setPosition(width / constants::MAX_NUMBER_OF_STATISTICS_ITEMS + posX, 
			i * height / constants::MAX_NUMBER_OF_STATISTICS_ITEMS + height / constants::MAX_NUMBER_OF_STATISTICS_ITEMS / 2 + posY);
		text[i].setCharacterSize(constants::SizeOfSquare / 6 * 5);
		SetStatistics(values[i], i);
		//text[i].setString(constants::statisticsText[i] + std::to_string(static_cast<long>(values[i])));
		
	}
	
}
/// <summary>
/// Deconstructor
/// </summary>
StatisticBox::~StatisticBox()
{
}
/// <summary>
/// Method to draw statistic box
/// </summary>
/// <param name="window">Render window</param>
void StatisticBox::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < constants::MAX_NUMBER_OF_STATISTICS_ITEMS; i++)
	{
		window.draw(text[i]);
	}
}
/// <summary>
/// Method wich set value of statistic
/// </summary>
/// <param name="value">Value to set</param>
/// <param name="type">Statistic in wich set</param>
void StatisticBox::SetStatistics(long double value, int type)
{
	if (type < 0 || type >= constants::MAX_NUMBER_OF_STATISTICS_ITEMS)
		exit(-4);
	if (type == static_cast<int>(constants::Stat::BOT))
	{
		this->values[type] = value;
		text[type].setString(constants::statisticsText[type] + (value?"Enabled":"Disabled"));
		return;
	}
	if (type == static_cast<int>(constants::Stat::DIFFICULTY))
	{
		this->values[type] = value;
		text[type].setString(constants::statisticsText[type] + constants::difficultyMenu[static_cast<int>(value) - 1]);
		return;
	}
	this->values[type] = value;
	text[type].setString(constants::statisticsText[type] + std::to_string(static_cast<long>(value)));
}
/// <summary>
/// Getter for statistic
/// </summary>
/// <param name="type">Statistic to get</param>
/// <returns>Return value of choosen statistic</returns>
long double StatisticBox::GetStatistics(int type)
{
	if (type < 0 || type >= constants::MAX_NUMBER_OF_STATISTICS_ITEMS)
		exit(-5);
	return values[type];
}
