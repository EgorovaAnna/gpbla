//#include "GeoObject.h"
//#include "PVO.h"
#include "MapImage.h"

int main()
{
	/*ofstream fout("map.pnm");
	fout << "P3" << '\n' << "900 500" << '\n';
	for (int i = 0; i < 900; i++)
		for (int j = 0; j < 500; j++)
			fout << "255 255 255" << '\n';
	fout.close();*/
	//GeoObject gob(5, 5, 1);
	//cout << gob.onWay(0, 0, 10, 10) << '\n';
	//Object a = gob.point(0, 0, 10, 10);
	//cout << a.getX() << " " << a.getY() << '\n';
	PVO pvo(4.5, 5.5, 4, 0.7);
	//cout << pvo.compile(5, 5, 1) << '\n';
	Map map(10, 100, 40, 90);
	map.addAim(Aim(20, 44, 0));
	map.addAim(Aim(17, 60, 0));
	map.addAim(Aim(70, 69, 0));
	map.addAim(Aim(90, 45, 0));
	map.addAim(Aim(90, 65, 0));
	map.addAim(Aim(40, 88, 0));
	map.addAim(Aim(12, 80, 0));
	map.addAim(Aim(70, 57, 0));
	map.addAim(Aim(90, 79, 0));
	map.addAim(Aim(95, 73, 0));
	map.addAim(Aim(53, 42, 0));
	map.addAim(Aim(55, 83, 0));
	map.addUAV(UAV(50, 50, 0, 0));
	map.addUAV(UAV(50, 50, 0, 0));
	map.addUAV(UAV(50, 50, 0, 0));
	//map.addUAV(UAV(50, 50, 0, 0));
	map.addObject(GeoObject(30, 60, 0.9));
	map.addObject(GeoObject(50, 60, 0.8));
	map.addObject(GeoObject(80, 70, 0.8));
	map.addObject(GeoObject(45, 89, 0.8));
	map.addObject(GeoObject(30, 42, 0.8));
	map.addObject(GeoObject(65, 62, 0.8));
	map.addObject(GeoObject(80, 48, 0.8));
	map.addObject(GeoObject(16, 68, 0.9));
	map.addObject(GeoObject(55.5, 68, 5.5));
	map.divideTer();
	MapImage mi(map);
	mi.loadFile("map.ppm");
	vector<UAV> u = map.getUAV();
	vector<GeoObject> o = map.getO();
	vector<Object> n;
	vector<Aim> a = map.getA();
	//cout << '\n'; cout << '\n'; cout << '\n';
	for (int i = 0; i < u.size(); i++)
		mi.paintLine(n = u[i].getRoat());
	//for (int i = 0; i < o.size(); i++)
	//cout << "point1" << '\n';
	//for (int i = 0; i < o.size(); i++)
	//	cout << o[i].getX() << "; " << o[i].getY() << "     ";
	//cout << '\n';
	mi.paintObjects(o);
	//cout << "point2" << '\n';
	mi.paintAims(a);
	mi.print("map1.pnm");
	//map.addUAV(UAV(50, 50, 0, 0));
	return 0;
}
