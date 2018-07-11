#include "Aim.h"

Aim::Aim(float nx, float ny, float nz, bool npvo) : Object(nx, ny, npvo)
{
	z = nz;
};
float Aim::getH()
{
    return z;
};
bool Aim::operator ==(Aim a2)
{
	if (a2.getX() == x && a2.getY() == y)
		return true;
	return false;
};
