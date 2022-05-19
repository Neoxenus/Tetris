#include "Point.h"
/// <summary>
/// Default constructor
/// </summary>
Point::Point()
{
	x = -1;
	y = -1;
}
/// <summary>
/// Constructor with parameters
/// </summary>
/// <param name="x">X of point</param>
/// <param name="y">Y of point</param>
Point::Point(int x = 0, int y = 0)
{
	this->x = x;
	this->y = y;
}
/// <summary>
/// Deconstructor
/// </summary>
Point::~Point()
{
}
