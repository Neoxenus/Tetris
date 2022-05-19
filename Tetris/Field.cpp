#include "Field.h"
/// <summary>
/// Constructor wich set size off field and else useful parameters
/// </summary>
/// <param name="heightBlocks">Height in blocks</param>
/// <param name="widthBlocks">Width in blocks</param>
/// <param name="height">Height of part of field from top to work area</param>
/// <param name="delay">Delay of field to fall tetromino</param>
/// <param name="offsetX">X offset to spawn tetromino</param>
/// <param name="offsetY">Y offset to spawn tetromino</param>
Field::Field(int heightBlocks, int widthBlocks, int height, double delay, int offsetX, int offsetY)
{
	this->defaultDelay = delay;
	this->heightBlocks = heightBlocks;
	this->widthBlocks = widthBlocks;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->height = height;
	this->isDelayDynamic = false;
	if (widthBlocks / 2 - 2 < 0)
		posForSpawnX = 0;
	else
		this->posForSpawnX = widthBlocks / 2 - 2;
	if (heightBlocks / 2 > 5)
		this->posForSpawnY = 0;
	else
		this->posForSpawnY = heightBlocks / 2 - 1;
	this->delay = delay;
	height = 5;
	this->clearField();
	ups = std::vector<int>(widthBlocks, 0);
}

Field::~Field()
{
}
/// <summary>
/// Updating of field
/// </summary>
/// <returns>Return number of lined wich will break</returns>
int Field::update()
{
	int k = heightBlocks - 1, numberOfLines = 0;
	for (int i = heightBlocks - 1; i >= 0; i--)
	{
		int count = 0;
		for (int j = 0; j < widthBlocks; j++)
		{
			if (field[i][j])
				count++;
			field[k][j] = field[i][j];
		}
		if (count < widthBlocks)
		{
			k--;
		}
		else
		{
			numberOfLines++;
		}

	}
	for (int i = 0; i < widthBlocks; i++)
	{
		ups[i] -= numberOfLines;
		if (ups[i] < 0)
		{
			ups[i] = 0;
			continue;
		}
		while (ups[i]>0 && this->GetElemField(heightBlocks - 1 - ups[i], i) == 0)
		{
			ups[i]--;
		}
	}
	return numberOfLines;
}
/// <summary>
/// One of getters to get position of spawn for figure
/// </summary>
/// <returns>Return X of position</returns>
int Field::Get_posForSpawnX()
{
	return posForSpawnX;
}
/// <summary>
/// One of getters to get position of spawn for figure
/// </summary>
/// <returns>Return Y of position</returns>
int Field::Get_posForSpawnY()
{
	return posForSpawnY;
}
/// <summary>
/// Get height of field
/// </summary>
/// <returns>Return height in blocks</returns>
int Field::getHeightBlocks()
{
	return this->heightBlocks;
}
/// <summary>
/// Get width of field
/// </summary>
/// <returns>Return width in blocks</returns>
int Field::getWidthBlocks()
{
	return this->widthBlocks;
}

int Field::Get_height()
{
	return this->height;
}
/// <summary>
/// Get element of field in some position
/// </summary>
/// <param name="y">Y of position</param>
/// <param name="x">X of position</param>
/// <returns></returns>
int Field::GetElemField(int y, int x)
{
	if (x >= widthBlocks || x<0 || y>=heightBlocks || y < 0)
	{
		std::cerr << "Incorrect arguments in function \"int Field::GetElemField(int x, int y)\"";
		exit(-2);
	}

	return this->field[y][x];
}
/// <summary>
/// Set element in some position
/// </summary>
/// <param name="x">X of position</param>
/// <param name="y">Y of position</param>
/// <param name="val">Value to set</param>
void Field::SetElemField(int x, int y, int val)
{
	if (x >= widthBlocks || x<0 || y>= heightBlocks || y < 0)
	{
		std::cerr << "Incorrect arguments in function \"void Field::SetElemField(int x, int y, int val)\"";
		exit(-3);
	}
	if (ups[x] < (heightBlocks - y))
		ups[x] = heightBlocks - y;
	field[y][x] = val;
	return;
}
/// <summary>
/// Setter for delay value
/// </summary>
/// <param name="delay">New delay of field</param>
void Field::SetDelay(double delay)
{
	this->delay = delay;
	return;
}
/// <summary>
/// Getter for delay value
/// </summary>
/// <returns>Return delay value</returns>
double Field::GetDelay()
{
	return this->delay;
}
/// <summary>
/// Method to reset delay to default value
/// </summary>
void Field::ResetDelay()
{
	delay = defaultDelay;
}
/// <summary>
/// Mehhod to draw field
/// </summary>
/// <param name="window">Render window</param>
/// <param name="cell">Object-helper</param>
void Field::draw(sf::RenderWindow& window, Cell cell)
{
	sf::RectangleShape border(sf::Vector2f(widthBlocks * constants::SizeOfSquare, constants::borderThickness));//up border
	border.setFillColor(sf::Color::Red);
	border.setPosition(sf::Vector2f(0, height * constants::SizeOfSquare));
	border.move(sf::Vector2f(offsetX, offsetY));
	border.move(constants::borderThickness, 0);
	window.draw(border);

	border.setPosition(sf::Vector2f(0, heightBlocks * constants::SizeOfSquare + constants::borderThickness));//down border
	border.move(sf::Vector2f(offsetX , offsetY ));
	border.move(constants::borderThickness, 0);
	window.draw(border);

	border.setSize(sf::Vector2f(heightBlocks * constants::SizeOfSquare + 2 * constants::borderThickness, constants::borderThickness));//left border
	border.setPosition(sf::Vector2f(constants::borderThickness, 0));
	border.rotate(90.f);
	border.move(sf::Vector2f(offsetX, offsetY));
	window.draw(border);

	border.move(constants::borderThickness, 0);
	border.move(sf::Vector2f(widthBlocks * constants::SizeOfSquare, 0));//right border
	window.draw(border);
	for (int i = 0; i < heightBlocks; i++)
		for (int j = 0; j < widthBlocks; j++)
		{
			if (this->GetElemField(i, j) == 0)
				continue;
			cell.setCell(j, i, offsetX, offsetY, this->GetElemField(i, j));
			cell.draw(window);
		}
}
/// <summary>
/// Getter for offset to spawn tetromino
/// </summary>
/// <returns>Return X of offset</returns>
int Field::GetOffsetX()
{
	return offsetX;
}
/// <summary>
/// Getter for offset to spawn tetromino
/// </summary>
/// <returns>Return Y of offset</returns>
int Field::GetOffsetY()
{
	return offsetY;
}
/// <summary>
/// Method to clear field
/// </summary>
void Field::clearField()
{
	field = std::vector<std::vector<int>>(heightBlocks, std::vector<int>(widthBlocks, 0));
	return;
}
/// <summary>
/// Method to set default delay
/// </summary>
/// <param name="delay">New default delay</param>
void Field::SetDefaultDelay(double delay)
{
	this->delay = delay;
	this->defaultDelay = delay;
	this->isDelayDynamic = false;
	return;
}
/// <summary>
/// Method to check game over state
/// </summary>
/// <returns>Return trur if it's game over</returns>
bool Field::isOver()
{
	int i = height - 1;
	for (int j = 0; j < widthBlocks; j++)
	{
		if (field[i][j])
		{
			return true;
		}
	}
	return false;
}
/// <summary>
/// Method to set dynamic delay
/// </summary>
void Field::setDynamicDelay()
{
	this->isDelayDynamic = true;
	delay = getDynamicDelay(0);
	defaultDelay = getDynamicDelay(0);
}
/// <summary>
/// Method to update dynamic delay with time variable
/// </summary>
/// <param name="time">Current time from beggining of the game</param>
void Field::updateDynamicDelay(double time)
{
	if (!isDelayDynamic)
		return;
	defaultDelay = getDynamicDelay(time);
	ResetDelay();
}
/// <summary>
/// Method to get the Y of position of top block
/// </summary>
/// <param name="x">X of block</param>
/// <returns>Y of top block with this X</returns>
int Field::GetUps(int x)
{
	if (x < 0 || x >= widthBlocks)
	{
		std::cerr << "Incorrect argument in function \"int Field::GetUps(int x)\"";
		exit(-1);
	}
	return ups[x];
}
/// <summary>
/// Overload of "operator=" to field class.
/// Copy the state of current field
/// </summary>
/// <param name="t"></param>
/// <returns></returns>
Field& Field::operator=(const Field& t)
{
	if (this == &t)
		return *this;
	this->field = t.field;
	this->ups = t.ups;
	return *this;
}

double Field::getDynamicDelay(double time)
{
	return 25.0/(50 + time);
}
