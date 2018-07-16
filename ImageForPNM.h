#ifndef IMAGEFORPNM_H
#define IMAGEFORPNM_H

#include "Point.h"
#include "Image.h"

class ImageForPNM : public Image
{
    Point **image;
public:
    ImageForPNM(int *tsize);
    void loadIm(std::string file);
    void paintAll(std::string color);
    void paintAll(int a, int b, int c);
    void drawPoint(int x, int y, std::string color);
    void drawPoint(int x, int y, int color[3]);
    void drawLine(int x1, int x2, int y1, int y2, std::string color);
    void paint();
    void showFile(std::string file);
    ~ImageForPNM();
private:
    int* colorFromString(std::string color);
};

#endif // IMAGEFORPNM_H
