#include "Object.h"

Object::Object(double nx, double ny, double nh, bool npvo)
{
    x = nx;
    y = ny;
    height = nh;
    pvo = npvo;
}
Object::Object(double nx, double ny, bool npvo)
{
	x = nx;
	y = ny;
	pvo = npvo;
}
Object::Object(bool npvo)
{
    pvo = npvo;
};
bool Object::isPVO()
{
	return pvo;
}
double Object::getX()
{
	return x;
}
double Object::getY()
{
	return y;
}
double Object::getH()
{
    return height;
}
void Object::setX(double nx)
{
	x = nx;
}
void Object::setY(double ny)
{
	y = ny;
}
void Object::setH(double nh)
{
    height = nh;
}
bool Object::operator()(Object a, Object b)
{
	return distance(a) < distance(b);
}
double Object::distance(Object b)
{
    return  pow(pow(x - b.getX(), 2) + pow(y - b.getY(), 2), 0.5);
}
double Object::distanceDegree(Object b)
{
    return pow(pow((x - b.getX())*111300*cos((y + b.getY())*3.14/360), 2) + pow((y - b.getY())*111300, 2), 0.5);
}
double Object::distanceXY(double bx, double by)
{
	return pow(pow(x - bx, 2) + pow(y - by, 2), 0.5);
}
