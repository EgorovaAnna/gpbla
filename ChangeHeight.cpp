#include "ChangeHeight.h"

ChangeHeight::ChangeHeight() : Object()
{

}
ChangeHeight::ChangeHeight(Object o) : Object(o)
{

}
ChangeHeight::ChangeHeight(double nx, double ny, double nh, bool npvo) : Object(nx, ny, nh, npvo)
{
};
ChangeHeight::ChangeHeight(Aim aim) : Object(aim.getX(), aim.getY(), aim.getH(), false)
{
};
bool ChangeHeight::upper(double h)
{
	if (h > height)
		return true;
	return false;
};
void ChangeHeight::operator =(Aim aim)
{
    x = aim.getX();
    y = aim.getY();
    height = aim.getH();
    pvo = false;
};
void ChangeHeight::operator =(GeoObject go)
{
    x = go.getX();
    y = go.getY();
    height = go.getH();
    pvo = false;
};
void ChangeHeight::operator =(Object o)
{
    x = o.getX();
    y = o.getY();
    height = o.getH();
    pvo = false;
};
