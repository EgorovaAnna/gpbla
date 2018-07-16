#include "ImageForPNM.h"

ImageForPNM::ImageForPNM(int *tsize) : Image(tsize)
{
    image = new Point* [sizeI[0]];
    for(int i = 0; i < sizeI[0]; i++)
        image[i] = new Point [sizeI[1]];
}
void ImageForPNM::paintAll(std::string color)
{
    int i, j;
    for(j = getY() - 1; j >= 0; j--)
        for(i = 0; i < getX(); i++)
            drawPoint(i, j, color);
}
void ImageForPNM::paintAll(int a, int b, int c)
{
    int i, j, color[3];
    color[0] = a; color[1] = b; color[2] = c;
    for(j = getY() - 1; j >= 0; j--)
        for(i = 0; i < getX(); i++)
            drawPoint(i, j, color);
}

void ImageForPNM::loadIm(std::string file)
{
    int i, j, k, a[3];
    std::string buf;
    std::ifstream fin;
    fin.open(file.c_str());
    fin >> buf >> buf >> buf >> buf;
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
void ImageForPNM::drawPoint(int x, int y, std::string color)
{
    if((x < getX())&&(y < getY()))
        image[x][y].init(colorFromString(color));
}
void ImageForPNM::drawPoint(int x, int y, int color[3])
{
    if((x < getX())&&(y < getY()))
        image[x][y].init(color);
}
void ImageForPNM::drawLine(int x1, int y1, int x2, int y2, std::string color)
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
                drawPoint(x1, i, color);
        }
        if(y1 == y2)
        {
            for (i = x1; i!= x2; i = i + signX)
                drawPoint(i, y1, color);
        }
    }
    else
    {
        drawPoint(x2, y2, color);
        while(x1 != x2 || y1 != y2)
        {
            drawPoint(x1, y1, color);
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
void ImageForPNM::showFile(std::string file)
{
    ofstream fout;
    int i, j, k;
    fout.open(file.c_str());
    fout << "P3" << '\n';
    fout << getX() << " " << getY() << '\n';
    for(j = getY() - 1; j >= 0; j--)
        for(i = 0; i < getX(); i++)
            for(k = 0; k < 3; k++)
                fout << image[i][j][k] << '\n';
}
int* ImageForPNM::colorFromString(std::string color)
{
    int *color3 = new int[3];
    color3[0] = 0; color3[1] = 0; color3[2] = 0;
    if (color == "red" || color == "white")
        color3[0] = 255;
    if (color == "blue" || color == "white")
        color3[2] = 255;
    if (color == "green" || color == "white")
        color3[1] = 255;
    return color3;
}
ImageForPNM::~ImageForPNM()
{
    for (int i = 0; i < sizeI[0]; i++)
        delete [] image[i];
    delete [] image;
}
