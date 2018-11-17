#include "PVO.h"

PVO::PVO(double nx, double ny, double nr, double np) : GeoObject(nx, ny, nr, true)
{
	p = np;
};
bool PVO::compile(double xuva, double yuva, double zuva)
{
	//cout << pow(pow(xuva - x, 2) + pow(yuva - y, 2) + pow(zuva - radius, 2), 0.5) << "  " << radius << " " << p*100 << '\n';
	if (pow(pow(xuva - x, 2) + pow(yuva - y, 2) + pow(zuva - radius, 2), 0.5) <= radius)
	{
		if (rand()%100 <= p*100)
			return true;
	}
	return false;
};
