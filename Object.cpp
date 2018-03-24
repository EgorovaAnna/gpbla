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
