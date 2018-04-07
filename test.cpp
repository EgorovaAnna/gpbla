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
	map.addAim(Aim(70, 89, 0));
	map.addAim(Aim(90, 45, 0));
	map.addAim(Aim(90, 65, 0));
	map.addAim(Aim(40, 88, 0));
	map.addAim(Aim(12, 80, 0));
	map.addAim(Aim(70, 57, 0));
	map.addAim(Aim(40, 79, 0));
	map.addAim(Aim(95, 73, 0));
	map.addAim(Aim(53, 42, 0));
	map.addAim(Aim(55, 83, 0));
	map.addUAV(UAV(50, 50, 0, 0));
	map.addUAV(UAV(50, 50, 0, 0));
	map.addUAV(UAV(50, 50, 0, 0));
	//map.addUAV(UAV(50, 50, 0, 0));
	map.addObject(GeoObject(36, 60, 1.9));
	map.addObject(GeoObject(84, 80, 1));
	map.addObject(GeoObject(80, 61, 1.3));
	map.addObject(GeoObject(45, 86, 1));
	map.addObject(GeoObject(30, 43, 1.2));
	map.addObject(GeoObject(65, 62, 1));
	map.addObject(GeoObject(80, 46, 1.5));
	map.addObject(GeoObject(24, 71.5, 1.1));
	map.addObject(GeoObject(55.5, 68, 5.5));
	map.divideTer();
	MapImage mi(map);
	mi.loadFile("map.ppm");
	vector<UAV> u = map.getUAV();
	vector<GeoObject> o = map.getO();
	vector<Object> n, d;
	vector<Line> k = map.getK();
	vector<Aim> a = map.getA();
	//cout << '\n'; cout << '\n'; cout << '\n';
	mi.paintAims(a);
	mi.print("mapAims.pnm");
	mi.paintObjects(o);
	mi.print("mapObjects.pnm");
	float x, y;
	for (int i = 0; i < k.size(); i++)
	{
		if (k[i][0] <= 3.14/2)
		{	
			y = min(map[3], tan(k[i][0])*map[1] + k[i][1]);
			if (tan(k[i][0]) == 0)
				x = map[1];
			else
				x = (y - k[i][1])/tan(k[i][0]);
		}
		else if (k[i][0] <= 3.14)
		{	
			y = min(map[3], tan(k[i][0])*map[0] + k[i][1]);
			x = max(map[0], (y - k[i][1])/tan(k[i][0]));
		}
		else if (k[i][0] <= 3.14*3/2)
		{	
			y = max(map[2], tan(k[i][0])*map[0] + k[i][1]);
			x = max(map[0], (y - k[i][1])/tan(k[i][0]));
		}
		else 
		{	
			y = max(map[2], tan(k[i][0])*map[1] + k[i][1]);
			x = min(map[1], (y - k[i][1])/tan(k[i][0]));
		}
		d.push_back(Object(x, y));
		d.push_back(Object(u[0].getX(), u[0].getY()));
	}
	mi.paintLine(d, 0);
	mi.print("mapDivision.pnm");
	for (int i = 0; i < u.size(); i++)
		mi.paintLine(n = u[i].getRoat());
	mi.print("mapRoats.pnm");
	//for (int i = 0; i < o.size(); i++)
	//cout << "point1" << '\n';
	//for (int i = 0; i < o.size(); i++)
	//	cout << o[i].getX() << "; " << o[i].getY() << "     ";
	//cout << '\n';
	//cout << "point2" << '\n';
	//map.addUAV(UAV(50, 50, 0, 0));
	return 0;
}
