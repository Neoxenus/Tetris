#include "Field.h"

Field::Field(int heightBlocks, int widhtBlocks, int height, double delay, int offsetX, int offsetY)
{
	this->defaultDelay = delay;
	this->heightBlocks = heightBlocks;
	this->widthBlocks = widhtBlocks;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->height = height;
	this->isDelayDynamic = false;
	if (widhtBlocks / 2 - 2 < 0)
		posForSpawnX = 0;
	else
		this->posForSpawnX = widhtBlocks / 2 - 2;
	if (heightBlocks / 2 > 5)
		this->posForSpawnY = 0;
	else
		this->posForSpawnY = heightBlocks / 2 - 1;
	this->delay = delay;
	height = 5;
	this->clearField();
	ups = std::vector<int>(widhtBlocks, 0);
}

Field::~Field()
{
}

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

int Field::Get_posForSpawnX()
{
	return posForSpawnX;
}

int Field::Get_posForSpawnY()
{
	return posForSpawnY;
}

int Field::getHeightBlocks()
{
	return this->heightBlocks;
}

int Field::getWidthBlocks()
{
	return this->widthBlocks;
}

int Field::Get_height()
{
	return this->height;
}

int Field::GetElemField(int y, int x)
{
	if (x >= widthBlocks || x<0 || y>=heightBlocks || y < 0)
	{
		std::cerr << "Incorrect arguments in function \"int Field::GetElemField(int x, int y)\"";
		exit(-2);
	}

	return this->field[y][x];
}

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

void Field::SetDelay(double delay)
{
	this->delay = delay;
	return;
}

double Field::GetDelay()
{
	return this->delay;
}

void Field::ResetDelay()
{
	delay = defaultDelay;
}

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

int Field::GetOffsetX()
{
	return offsetX;
}

int Field::GetOffsetY()
{
	return offsetY;
}

void Field::clearField()
{
	field = std::vector<std::vector<int>>(heightBlocks, std::vector<int>(widthBlocks, 0));
	return;
}

void Field::SetDefaultDelay(double delay)
{
	this->delay = delay;
	this->defaultDelay = delay;
	this->isDelayDynamic = false;
	return;
}

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

void Field::setDynamicDelay()
{
	this->isDelayDynamic = true;
	delay = getDynamicDelay(0);
	defaultDelay = getDynamicDelay(0);
}

void Field::updateDynamicDelay(double time)
{
	if (!isDelayDynamic)
		return;
	defaultDelay = getDynamicDelay(time);
	ResetDelay();
}

int Field::GetUps(int x)
{
	if (x < 0 || x >= widthBlocks)
	{
		std::cerr << "Incorrect argument in function \"int Field::GetUps(int x)\"";
		exit(-1);
	}
	return ups[x];
}

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
