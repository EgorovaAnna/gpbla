#include "Object.h"

Object::Object(float nx, float ny, bool npvo)
{
	x = nx;
	y = ny;
	pvo = npvo;
}
bool Object::isPVO()
{
	return pvo;
}
float Object::getX()
{
	return x;
}
float Object::getY()
{
	return y;
}
void Object::setX(float nx)
{
	x = nx;
}
void Object::setY(float ny)
{
	y = ny;
}
bool Object::operator()(Object a, Object b)
{
	return distance(a) < distance(b);
}
float Object::distance(Object b)
{
	return pow(pow(x - b.getX(), 2) + pow(y - b.getY(), 2), 0.5);
}
float Object::distanceXY(float bx, float by)
{
	return pow(pow(x - bx, 2) + pow(y - by, 2), 0.5);
}
