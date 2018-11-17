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
    double x, y, height;
	bool pvo;
public:
    Object(double nx, double ny, double nh, bool npvo = false);
    Object(bool npvo = false);
    Object(double nx, double ny, bool npvo = false);
	bool isPVO(); 
    double getX();
    double getY();
    double getH();
    void setX(double nx);
    void setY(double ny);
    void setH(double nh);
	bool operator()(Object a, Object b);
    double distance(Object b);
    double distanceDegree(Object b);
    double distanceXY(double x, double y);
};
class Line
{
    double k, b;
public:
    Line(double nk, double nb)
	{
		k = nk;
		b = nb;
	};
    double operator[](int a)
	{
		if (a == 0)
			return k;
		else
			return b;
	};
    void setK(double nk)
	{
		k = nk;
	};
    void setB(double nb)
	{
		b = nb;
	};
};

#endif
