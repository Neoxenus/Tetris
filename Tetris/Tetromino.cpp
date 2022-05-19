#include "Tetromino.h"
/// <summary>
/// Constructor
/// </summary>
/// <param name="A">Field in wich we create tetromino</param>
Tetromino::Tetromino(Field& A) : field(A) {
}

Tetromino::~Tetromino()
{
}

bool Tetromino::check()
{
	for (int i = 0; i < 4; i++)
	{
		if (a[i].x < 0 || a[i].x >= field.getWidthBlocks() || a[i].y > field.getHeightBlocks() || a[i].y < 0)
			return false;
		else if (field.GetElemField(a[i].y, a[i].x))
			return false;
	}
	return true;
}

bool Tetromino::checkUnder()
{
	for (int i = 0; i < 4; i++)
	{
		if (a[i].y+1 >= field.getHeightBlocks() || (field.GetElemField(a[i].y + 1, a[i].x)))
			return false;
	}
	return true;

}
/// <summary>
/// Method to rotate tetromino
/// </summary>
void Tetromino::rotate()
{
	if (this->type == static_cast<int>(constants::TetrominoType::O))
	{
		return;
	}
	int x,y, x0, y0;
	x0 = a[1].x;
	y0 = a[1].y;
	for (int i = 0; i < 4; i++)
	{
		y = a[i].y - y0;
		x = a[i].x - x0;
		a[i].x = x0 - y;
		a[i].y = y0 + x;
	}
	if (this->check())
		return;	
	for (int i = 0; i < 4; i++)
		a[i] = b[i];
}
/// <summary>
/// Method to horizontal move of tetromino
/// </summary>
/// <param name="dx">Horizontal offset</param>
/// <returns>Return true if horizontal move successful</returns>
bool Tetromino::horizontalMoving(int dx)
{
	bool flag;
	for (int i = 0; i < 4; i++)
	{
		b[i] = a[i];
		a[i].x += dx;
	}
	flag = this->check();
	if (!flag)
		for (int i = 0; i < 4; i++)
			a[i] = b[i];
	return flag;
}
/// <summary>
/// Method to fall tetromin in one block
/// </summary>
/// <returns>Return true if can't fall again</returns>
bool Tetromino::falling()
{
	for (int i = 0; i < 4; i++)
	{
		b[i] = a[i];
		a[i].y += 1;
	}
	if (!this->checkUnder())
	{
		for (int i = 0; i < 4; i++)
			field.SetElemField(a[i].x, a[i].y, color);
		return true;
	}
	return false;
}
/// <summary>
/// Method to create new tetromino
/// </summary>
/// <param name="A">New field</param>
void Tetromino::newTetromino(Field& A)
{
	this->field = A;
	static bool flag = false;
	if (!flag)
	{
		srand(static_cast<time_t>(time(NULL)));
		flag = true;
	}
	this->type = rand() % constants::NUMBER_TYPES_TETROMINO;
	this->color = 1 + rand() % constants::MAX_NUMBER_COLORS;
	this->offsetX = field.GetOffsetX();
	this->offsetY = field.GetOffsetY();
	for (int i = 0; i < 4; i++)
	{
		a[i].x = constants::figures[type][i] / 2 + field.Get_posForSpawnX();
		a[i].y = constants::figures[type][i] % 2 + field.Get_posForSpawnY();
		b[i] = a[i];
	}
}

int Tetromino::GetColor()
{
	return this->color;
}

int Tetromino::GetType()
{
	return this->type;
}

int Tetromino::Get_x(int i)
{
	if (i < 0 || i >= 4)
	{
		std::cerr << "Incorrect argument int i in function int Get_x(int)\n";
		exit(-6);
	}
	return a[i].x;
}

int Tetromino::Get_y(int i)
{
	if (i < 0 || i >= 4)
	{
		std::cerr << "Incorrect argument int i in function int Get_y(int)\n";
		exit(-7);
	}
	return a[i].y;
}
/// <summary>
/// Method to draw tetromino
/// </summary>
/// <param name="window">Render window</param>
/// <param name="cell">Object-heler</param>
void Tetromino::draw(sf::RenderWindow& window, Cell cell)
{
	for (int i = 0; i < 4; i++)
	{
		cell.setCell(this->Get_x(i), this->Get_y(i), offsetX, offsetY, this->GetColor());
		cell.draw(window );
	}
}

void Tetromino::changeField(Field& B)
{
	this->offsetX = B.GetOffsetX();
	this->offsetY = B.GetOffsetY();
	for (int i = 0; i < 4; i++)
	{
		a[i].x = constants::figures[type][i] / 2 + B.Get_posForSpawnX();
		a[i].y = constants::figures[type][i] % 2 + B.Get_posForSpawnY();
		b[i] = a[i];
	}
}

/// <summary>
/// Overload of operator=.
/// Copy the state of tetromino
/// </summary>
/// <param name="t">Tetromino to copy</param>
/// <returns>Return referense to new tetromino</returns>
Tetromino& Tetromino::operator = (const Tetromino& t)
{
	if (this == &t)
		return *this;
	this->color = t.color;
	this->type = t.type;
	for (int i = 0; i < 4; i++)
	{
		this->a[i] = t.a[i];
		this->b[i] = t.b[i];
	}
	return *this;
}
