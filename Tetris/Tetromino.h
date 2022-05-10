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
	Tetromino(Field& A) : field(A) {
	}
	~Tetromino();
	void newTetromino(Field& A);
	Tetromino& operator=(const Tetromino& t);
	//control
	void rotate();
	bool horizontalMoving(int dx);
	bool falling();
	//bot
	int GetType();
	int Get_x(int i);
	int Get_y(int i);


	void draw(sf::RenderWindow& window, Cell cell);
private:
	int color, type, offsetX, offsetY;
	Point a[4], b[4];
	Field& field;

	bool check();
	bool checkUnder();
	int GetColor();
	void changeField(Field& B);

};