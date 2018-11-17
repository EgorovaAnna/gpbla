#include "Aim.h"

Aim::Aim(double nx, double ny, double nz, bool npvo) : Object(nx, ny, nz, npvo)
{
};
bool Aim::operator ==(Aim a2)
{
	if (a2.getX() == x && a2.getY() == y)
		return true;
	return false;
};
