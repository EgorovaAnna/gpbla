//#include "GeoObject.h"
//#include "PVO.h"
#include "Map.h"

int main()
{
	GeoObject gob(5, 5, 1);
	//cout << gob.onWay(0, 0, 10, 10) << '\n';
	Object a = gob.point(0, 0, 10, 10);
	//cout << a.getX() << " " << a.getY() << '\n';
	PVO pvo(4.5, 5.5, 4, 0.7);
	//cout << pvo.compile(5, 5, 1) << '\n';
	Map map(0, 100, 0, 100);
	map.addAim(Aim(20, 20, 0));
	map.addAim(Aim(10, 60, 0));
	map.addAim(Aim(70, 60, 0));
	map.addAim(Aim(90, 20, 0));
	map.addAim(Aim(100, 20, 0));
	map.addAim(Aim(40, 20, 0));
	map.addAim(Aim(10, 80, 0));
	map.addAim(Aim(70, 30, 0));
	map.addAim(Aim(90, 90, 0));
	map.addAim(Aim(100, 73, 0));
	map.addUAV(UAV(50, 50, 0, 0));
	map.addUAV(UAV(50, 50, 0, 0));
	map.addUAV(UAV(50, 50, 0, 0));
	//map.addUAV(UAV(50, 50, 0, 0));
	map.divideTer();
	return 0;
}
