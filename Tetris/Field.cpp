#include "Field.h"

Field::Field(int M, int N, int height, double delay, int offsetX, int offsetY)
{
	this->defaultDelay = delay;
	this->M = M;
	this->N = N;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->height = height;
	this->isDelayDynamic = false;
	if (N / 2 - 2 < 0)
		posForSpawnX = 0;
	else
		this->posForSpawnX = N / 2 - 2;
	if (M / 2 > 5)
		this->posForSpawnY = 0;
	else
		this->posForSpawnY = M / 2 - 1;
	this->delay = delay;
	height = 5;
	this->clearField();
	ups = std::vector<int>(N, 0);
}

Field::~Field()
{
}

int Field::update()
{
	int k = M - 1, numberOfLines = 0;
	for (int i = M - 1; i >= 0; i--)
	{
		int count = 0;
		for (int j = 0; j < N; j++)
		{
			if (field[i][j])
				count++;
			field[k][j] = field[i][j];
		}
		if (count < N)
		{
			k--;
		}
		else
		{
			numberOfLines++;
		}

	}
	for (int i = 0; i < N; i++)
	{
		ups[i] -= numberOfLines;
		if (ups[i] < 0)
		{
			ups[i] = 0;
			continue;
		}
		while (ups[i]>0 && this->GetElemField(M - 1 - ups[i], i) == 0)
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

int Field::Get_M()
{
	return this->M;
}

int Field::Get_N()
{
	return this->N;
}

int Field::Get_height()
{
	return this->height;
}

int Field::GetElemField(int y, int x)
{
	if (x >= N || x<0 || y>=M || y < 0)
	{
		std::cerr << "Incorrect arguments in function \"int Field::GetElemField(int x, int y)\"";
		exit(-2);
	}

	return this->field[y][x];
}

void Field::SetElemField(int x, int y, int val)
{
	if (x >= N || x<0 || y>=M || y < 0)
	{
		std::cerr << "Incorrect arguments in function \"void Field::SetElemField(int x, int y, int val)\"";
		exit(-3);
	}
	if (ups[x] < (M - y))
		ups[x] = M - y;
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
	sf::RectangleShape border(sf::Vector2f(N * constants::SizeOfSquare, constants::borderThickness));//up border
	border.setFillColor(sf::Color::Red);
	border.setPosition(sf::Vector2f(0, height * constants::SizeOfSquare));
	border.move(sf::Vector2f(offsetX, offsetY));
	border.move(constants::borderThickness, 0);
	window.draw(border);

	border.setPosition(sf::Vector2f(0, M * constants::SizeOfSquare + constants::borderThickness));//down border
	border.move(sf::Vector2f(offsetX , offsetY ));
	border.move(constants::borderThickness, 0);
	window.draw(border);

	border.setSize(sf::Vector2f(M * constants::SizeOfSquare + 2 * constants::borderThickness, constants::borderThickness));//left border
	border.setPosition(sf::Vector2f(constants::borderThickness, 0));
	border.rotate(90.f);
	border.move(sf::Vector2f(offsetX, offsetY));
	window.draw(border);

	border.move(constants::borderThickness, 0);
	border.move(sf::Vector2f(N * constants::SizeOfSquare, 0));//right border
	window.draw(border);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
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
	field = std::vector<std::vector<int>>(M, std::vector<int>(N, 0));
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
	for (int j = 0; j < N; j++)
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
	if (x < 0 || x >= N)
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
	//this->delay = t.delay;
	//this->defaultDelay = t.defaultDelay;
	this->field = t.field;
	//this->height = t.height;
	//this->isDelayDynamic = t.isDelayDynamic;
	//this->M = t.M;
	//this->N = t.N;
	//this->offsetX = t.offsetX;
	//this->offsetY = t.offsetY;
	//this->posForSpawnX = t.posForSpawnX;
	//this->posForSpawnY = t.posForSpawnY;
	this->ups = t.ups;
	return *this;
}

double Field::getDynamicDelay(double time)
{
	return 25.0/(50 + time);
}
