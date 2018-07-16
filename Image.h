#ifndef Image_h
#define Image_h

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

class Image
{
protected:
	int sizeI[2];
public:
	Image(int *tsize);
    Image(int tx, int ty);
	int getX();
	int getY();
    virtual void loadIm(std::string file){};
    virtual void showFile(std::string file){};
    virtual void drawPoint(int x, int y, std::string color){};
    virtual void drawPoint(int x, int y, int color[3]){};
    virtual void drawLine(int x1, int x2, int y1, int y2, std::string color){};
    virtual void drawLine(int x1, int x2, int y1, int y2, int color[3]){};
    ~Image(){};
};

#endif
