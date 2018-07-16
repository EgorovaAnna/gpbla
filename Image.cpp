#include "Image.h"

Image::Image(int *tsize)
{
	sizeI[0] = tsize[0];
	sizeI[1] = tsize[1];
}
Image::Image(int tx, int ty)
{
    sizeI[0] = tx;
    sizeI[1] = ty;
}
int Image::getX()
{
    return sizeI[0];
}
int Image::getY()
{
    return sizeI[1];
}








