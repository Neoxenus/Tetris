#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

#include "Field.h"
#include "Point.h"
#include "Cell.h"
#include "Constants.h"
class Tetromino
{
public:
	//general
	Tetromino(Field A);
	~Tetromino();
	void newTetromino(Field A);
	Tetromino& operator=(const Tetromino& t);
	//control
	void rotate(Field A);
	bool horizontalMoving(Field A, int dx);
	bool falling(Field &A);
	//bot
	int GetType();
	int Get_x(int i);
	int Get_y(int i);

	void draw(sf::RenderWindow& window, Cell cell, Field A);
private:
	int color, type, offsetX, offsetY;
	Point a[4], b[4];

	bool check(Field A);
	bool checkUnder(Field A);
	int GetColor();
	void changeField(Field B);

};