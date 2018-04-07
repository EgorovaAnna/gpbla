#ifndef Point_h
#define Point_h

#include <iostream>
using namespace std;

class Point
{
	int point[3];
	int radius;
public:
	Point();
	Point(int a, int b, int c, int r = 0);
	void operator=(int a);
	int operator[](int a);
	void init(int a[3]);
	int getRadius();
	void setR(int r);
};
#endif
