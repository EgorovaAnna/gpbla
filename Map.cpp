#include "Map.h"


Map::Map(float nx1, float nx2, float ny1, float ny2)
{
	if (nx1 > nx2)
	{
		x2 = nx1; 
		x1 = nx2;
	}
	else
	{
		x1 = nx1; 
		x2 = nx2;
	}
	if (ny1 > ny2)
	{
		y2 = ny1; 
		y1 = ny2;
	}
	else
	{
		y1 = ny1; 
		y2 = ny2;
	}
};
void Map::addObject(GeoObject newGO)
{
	int a = 0;
	if (newGO.getX() <= x2 && newGO.getX() >= x1 && newGO.getY() >= y1 && newGO.getY() <= y2)
		for (auto i = objects.begin(); i < objects.end(); i++)
			if (objects[i] == newGO)
				a = 1;
		if (a == 0)
			objects.push_back(newGO);
		
}; 
void Map::addAim(Aim newAim)
{
	int a = 0;
	if (newAim.getX() <= x2 && newAim.getX() >= x1 && newAim.getY() >= y1 && newAim.getY() <= y2)
		for (auto i = aims.begin(); i < aims.end(); i++)
			if (aims[i] == newAim)
				a = 1;
		if (a == 0)
			aims.push_back(newAim);
};
void Map::addUAV(UAV nemUAV)
{
	uavs.push_back(uav);
};
void Map::readGIS(string file)
{
};
void Map::divideTer()
{
	vector<float[2]> kb; // так вообще можно?
	vector<Object> dirs;
	float (dxy = (x2 - x1 + y2 - y1)/50
	if (allUVAtogether())
	{
		int aimsInSector = aims.size()/uvas.size(); //что будем делать с углами, близкими к 90?
		for (int i = 0; i < uvas.size(); i++)
		{
			k.push_back({(360.0*i/(float)(uvas.size() - 1))*3.14/360, uvas[0].getY() - uvas[0].getX()*(360.0*i/(float)(uvas.size() - 1))*3.14/360});
			if (i > 0)
				dirs.push_back(Object(uvas[0].getX() + cos(k[i - 1] + (k[i] - k[i - 1])/2)*dxy, uvas[0].getY() + sin(k[i - 1] + (k[i] - k[i - 1])/2)*dxy)); 
		}
		for (int i = 1; i < uvas.size() - 1; i++)
		{
			if (k[i][0] < k[i - 1][0])
			{
				k[i][0] = k[i - 1][0];
				k[i][1] = k[i - 1][0];
			}
			while (calcAims(k[i - 1][0], k[i - 1][1], k[i][0], k[i][1], dirs[i - 1]) < aimsInSector) // пересчитывать направление
			{
				k[i][0] += 3.14/360;//подумать, какой будет сдвиг для луча
				k[i][1] = uvas[0].getY() - uvas[0].getX()*k[i][0];
			}
			while (calcAims(k[i - 1][0], k[i - 1][1], k[i][0], k[i][1], dirs[i - 1]) > aimsInSector + 1)
			{
				k[i][0] -= 3.14/360;
				k[i][1] = uvas[0].getY() - uvas[0].getX()*k[i][0];
			}
		}
		dirs.push_back(uvas[0].getX() + cos(k[uvas.size() - 1] + (2*3.14 - k[uvas.size() - 1])/2)*dxy, uvas[0].getY() + sin(k[uvas.size() - 1] + (2*3.14 - k[uvas.size() - 1])/2)*dxy));
		for (int i = 0; i < uvas.size() - 1; i++)
		{
			uavs[i].roat(aimsForUAV(k[i][0], k[i][1], k[i + 1][0], k[i + 1][1], dirs[i]));
			//uavs[i].elaborateRoat(goForUAV(k[i][0], k[i][1], k[i + 1][0], k[i + 1][1], dirs[i]));
		}
		uavs[i].roat(aimsForUAV(k[uvas.size() - 1][0], k[uvas.size() - 1][1], k[0][0], k[0][1], dirs[uvas.size() - 1]));
		//uavs[i].elaborateRoat(goForUAV(k[i][0], k[i][1], k[i + 1][0], k[i + 1][1], dirs[i]));
	}
	else
	{
	}
};
bool Map::allUVAtogether()
{
	float sum = 0;
	for (auto i = uvas.begin(); i < uvas.end() - 1; i++)
		sum += uvas[i].getX() - uvas[i + 1].getX() + uvas[i].getY() - uvas[i + 1].getY();
	if (sum < ((x1 + x2)/100 + (y1 + y2)/100)*uvas.size())
		return true;
	return false;
};
int Map::calcAims(float k1, float b1, float k2, float b2, Object dir) // будет косячить, если мы около нулевой широты/долготы
{
	int sum = 0, dirx, diry, k;
	if (k1 > k2)
	{
		k = k1;
		k1 = k2;
		k2 = k;
	}
	Object centr((b2 - b1)/(k1 - k2));
	dirx = centr.getX() - dir.getX(); //и вот тут еще что-то не то. потом переделать определение направления надо
	diry = centr.getY() - dir.getY();
	for (auto i = aims.begin(); i < aims.end(); i++)
	{
		k = atan((aims[i].getY() - centr.getY())/(aims[i].getX()));
		if (k >= k1 && k <= k2 && dirx*(centr.getX() - aims[i].getX()) >= 0 && diry*(centr.getY() - aims[i].getY()) >= 0)
			sum++;
	}
	return sum;
};
vector<Aim> Map::aimsForUAV(float k1, float b1, float k2, float b2, Object dir)
{
	int dirx, diry, k;
	vector<Aim> sum;
	if (k1 > k2)
	{
		k = k1;
		k1 = k2;
		k2 = k;
	}
	Object centr((b2 - b1)/(k1 - k2));
	dirx = centr.getX() - dir.getX();
	diry = centr.getY() - dir.getY();
	for (auto i = aims.begin(); i < aims.end(); i++)
	{
		k = atan((aims[i].getY() - centr.getY())/(aims[i].getX())); //какие значения? надо нормировать углы, чтобы попали в значения, возвращаемые арктангенсом
		if (k >= k1 && k <= k2 && dirx*(centr.getX() - aims[i].getX()) >= 0 && diry*(centr.getY() - aims[i].getY()) >= 0)
			sum.push_back(aims[i]);
	}
	return sum;
};
vector<GeoObject> Map::goForUAV(float k1, float b1, float k2, float b2, Object dir)
{
	int dirx, diry, k;
	vector<GeoObject> sum;
	if (k1 > k2)
	{
		k = k1;
		k1 = k2;
		k2 = k;
	}
	Object centr((b2 - b1)/(k1 - k2));
	dirx = centr.getX() - dir.getX();
	diry = centr.getY() - dir.getY();
	for (auto i = objects.begin(); i < objects.end(); i++)
	{
		k = atan((objects[i].getY() - centr.getY())/(objects[i].getX())); //какие значения? надо нормировать углы, чтобы попали в значения, возвращаемые арктангенсом
		if (k >= k1 && k <= k2 && dirx*(centr.getX() - objects[i].getX()) >= 0 && diry*(centr.getY() - objects[i].getY()) >= 0)
			sum.push_back(objects[i]);
	}
	return sum;
};




