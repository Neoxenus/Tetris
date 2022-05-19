#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

#include "Field.h"
#include "Point.h"
#include "Cell.h"
#include "Constants.h"
/// <summary>
/// Class to implement tetromino
/// </summary>
class Tetromino
{
public:
	//general
	Tetromino(Field& A);
	~Tetromino();
	void newTetromino(Field& A);
	Tetromino& operator=(const Tetromino& t);
	//control
	void rotate();
	bool horizontalMoving(int dx);
	bool falling();
	
	void draw(sf::RenderWindow& window, Cell cell);
	friend class Bot;
private:
	int color, type, offsetX, offsetY;
	Point a[4], b[4];
	Field& field;

	bool check();
	bool checkUnder();
	int GetColor();
	void changeField(Field& B);

	//bot
	int GetType();
	int Get_x(int i);
	int Get_y(int i);
};