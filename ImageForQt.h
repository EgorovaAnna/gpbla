#ifndef IMAGEFORQT_H
#define IMAGEFORQT_H

#include "Image.h"
#include <QImage>

class ImageForQt : public Image
{
    QImage *image;
public:
    ImageForQt(QImage *newimage);
    void loadIm(std::string file);
    void drawPoint(int x, int y, std::string color);
    void drawPoint(int x, int y, int color[3]);
    void drawLine(int x1, int y1, int x2, int y2, std::string color);
    void drawLine(int x1, int y1, int x2, int y2, int color[3]);
    void showFile(std::string file);
    ~ImageForQt(){};
};

#endif // IMAGEFORQT_H
