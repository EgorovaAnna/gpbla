#ifndef Object_h
#define Object_h

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <time.h>

using namespace std;

class Object
{
protected:
	float x, y; 
	bool pvo;
public:
	Object(float nx, float ny, bool npvo = false);
	bool isPVO(); 
	float getX();
	float getY();
	void setX(float nx);
	void setY(float ny);
	bool operator()(Object a, Object b);
	float distance(Object b);
	float distanceXY(float x, float y);
};
class Line
{
	float k, b;
public:
	Line(float nk, float nb)
	{
		k = nk;
		b = nb;
	};
	float operator[](int a)
	{
		if (a == 0)
			return k;
		else
			return b;
	};
	void setK(float nk)
	{
		k = nk;
	};
	void setB(float nb)
	{
		b = nb;
	};
};

#endif
