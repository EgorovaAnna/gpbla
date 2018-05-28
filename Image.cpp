#include "Image.h"
using namespace std;

Image::Image(int *tsize)
{
	int i;
	sizeI[0] = tsize[0];
	sizeI[1] = tsize[1];
	image = new Point* [sizeI[0]];
	for(i = 0; i < sizeI[0]; i++)
		image[i] = new Point [sizeI[1]];
}
void Image::paintAll(int color)
{
	int i, j, k;
	for(j = getY() - 1; j >= 0; j--)
		for(i = 0; i < getX(); i++)
			image[i][j] = color;
}
void Image::paintAll(int a, int b, int c)
{
	int i, j, color[3];
	color[0] = a; color[1] = b; color[2] = c; 
	for(j = getY() - 1; j >= 0; j--)
		for(i = 0; i < getX(); i++)
			image[i][j].init(color);
}
int Image::getX()
{
	return sizeI[0];
}
int Image::getY()
{
	return sizeI[1];
}
void Image::loadIm(std::ifstream &fin)
{
	int i, j, k, a[3];
	for(j = getY() - 1; j >= 0; j--)
	{
		for(i = 0; i < getX(); i++)
		{
			for(k = 0; k < 3; k++)
				fin >> a[k];
			image[i][j].init(a);
		}
	}
}
void Image::drawPoint(int x, int y, int color, int nh)
{
	if((x < getX())&&(y < getY()))
		image[x][y] = color;
}
void Image::drawPoint(int x, int y, int color[3], int nh)
{
	if((x < getX())&&(y < getY()))
		image[x][y].init(color);
}
void Image::drawLine(int x1, int y1, int x2, int y2, int color, int nh)
{
	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	int i;
	if (x1 == x2||y1 == y2)
	{
		if (x1 == x2)
		{
			for (i = y1; i!= y2; i = i + signY)
				drawPoint(x1, i, color, nh);
		}
		if(y1 == y2)
		{
			for (i = x1; i!= x2; i = i + signX)
				drawPoint(i, y1, color, nh);
		}
	}
	else
	{
		drawPoint(x2, y2, color, nh);	
		while(x1 != x2 || y1 != y2)
		{
			drawPoint(x1, y1, color, nh);
			int error2 = error*2;
			if (error2 > -deltaY)
			{
				error -= deltaY;
				x1 += signX;
			}
			if (error2 < deltaX)
			{
				error += deltaX;
				y1 += signY;
			}
		}
	}
}
void Image::showFile(std::string fl)
{
	ofstream fout;
	int i, j, k;
	fout.open(fl.c_str());
	fout << "P3" << '\n';
	fout << getX() << " " << getY() << '\n';
	for(j = getY() - 1; j >= 0; j--)
		for(i = 0; i < getX(); i++)
			for(k = 0; k < 3; k++)
				fout << image[i][j][k] << '\n';
}








