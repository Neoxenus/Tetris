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
	Tetromino(Field A);
	~Tetromino();
	bool check(Field A);
	bool checkUnder(Field A);
	void rotate(Field A);
	bool horizontalMoving(Field A, int dx);
	bool falling(Field &A);
	void newTetromino(Field A);
	int GetColor();
	int GetType();
	int Get_x(int i);
	int Get_y(int i);
	void draw(sf::RenderWindow& window, Cell cell, Field A);
	void changeField(Field B);
	Tetromino& operator=(const Tetromino& t);
private:
	int color, type, offsetX, offsetY;
	Point a[4], b[4];
};