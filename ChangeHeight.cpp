#include "ChangeHeight.h"

ChangeHeight::ChangeHeight(float nx, float ny, float nh, bool npvo) : Object(nx, ny, npvo)
{
	height = nh;
};
bool ChangeHeight::upper(float h)
{
	if (h > height)
		return true;
	return false;
};
