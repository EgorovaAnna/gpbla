#ifndef Image_h
#define Image_h

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include "Point.h"

class Image
{
	Point **image;
	int sizeI[2];
public:
	Image(int *tsize);
	int getX();
	int getY();
	void loadIm(std::ifstream &fin);
	void paintAll(int color);
	void paintAll(int a, int b, int c);
	void drawPoint(int x, int y, int color = 0, int nh = 0);
	void drawPoint(int x, int y, int color[3], int nh = 0);
	void drawLine(int x1, int x2, int y1, int y2, int color = 0, int nh = 0);
	void showFile(std::string fl);
	void paint();
};

#endif
