#include "ImageForQt.h"

ImageForQt::ImageForQt(QImage *newimage) : Image(newimage -> width(), newimage -> height())
{
    image = newimage;
}
void ImageForQt::loadIm(std::string file)
{
    image -> load(QString::fromStdString(file));
}

void ImageForQt::drawPoint(int x, int y, std::string color)
{
    image -> setPixelColor(x, y, QColor(QString::fromStdString(color)));
}
void ImageForQt::drawPoint(int x, int y, int color[])
{
    image -> setPixelColor(x, y, QColor(color[0], color[1], color[2]));
}
void ImageForQt::drawLine(int x1, int y1, int x2, int y2, int color[])
{
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    int i;
    if (x1 == x2 || y1 == y2)
    {
        if (x1 == x2)
        {
            for (i = y1; i!= y2; i = i + signY)
                drawPoint(x1, i, color);
        }
        if (y1 == y2)
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

void ImageForQt::drawLine(int x1, int y1, int x2, int y2, std::string color)
{
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    int i;
    if (x1 == x2 || y1 == y2)
    {
        if (x1 == x2)
        {
            for (i = y1; i!= y2; i = i + signY)
                drawPoint(x1, i, color);
        }
        if (y1 == y2)
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
void ImageForQt::showFile(std::string file)
{
    image -> save(QString::fromStdString(file));
}
