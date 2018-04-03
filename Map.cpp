#include "Map.h"
#define pi 3.14159265359


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
		for (int i = 0; i < objects.size(); i++)
			if (objects[i] == newGO)
				a = 1;
		if (a == 0)
			objects.push_back(newGO);
		
}; 
void Map::addAim(Aim newAim)
{
	int a = 0;
	if (newAim.getX() <= x2 && newAim.getX() >= x1 && newAim.getY() >= y1 && newAim.getY() <= y2)
		for (int i = 0; i < aims.size(); i++)
			if (aims[i] == newAim)
				a = 1;
		if (a == 0)
			aims.push_back(newAim);
};
void Map::addUAV(UAV newUAV)
{
	uavs.push_back(newUAV);
};
void Map::readGIS(string file)
{
};
void Map::divideTer()
{
	vector<Line> k;
	vector<Object> dirs;
	float dk;
	float dxy = (x2 - x1 + y2 - y1)/10;
	if (allUVAtogether())
	{
		int aimsInSector = aims.size()/uavs.size(); //что будем делать с углами, близкими к 90?
		for (int i = 0; i < uavs.size(); i++)
		{
			dk = i*360.0/(uavs.size());
			k.push_back(Line(dk*pi/180, uavs[0].getY() - uavs[0].getX()*tan(dk*pi/180)));
			if (i > 0)
				dirs.push_back(Object(uavs[0].getX() + cos(k[i - 1][0] + (k[i][0] - k[i - 1][0])/2)*dxy, uavs[0].getY() + sin(k[i - 1][0] + (k[i][0] - k[i - 1][0])/2)*dxy)); 
		}
		for (int i = 1; i < uavs.size(); i++)
		{
			if (k[i][0] < k[i - 1][0])
			{
				k[i].setK(k[i - 1][0]);
				k[i].setB(k[i - 1][1]);
			}
			while (calcAims(k[i - 1][0], k[i - 1][1], k[i][0], k[i][1], dirs[i - 1]) < aimsInSector) // пересчитывать направление
			{
				k[i].setK(k[i][0] + pi/180);//подумать, какой будет сдвиг для луча
				k[i].setB(uavs[0].getY() - uavs[0].getX()*tan(k[i][0]));
				dirs[i - 1].setX(uavs[0].getX() + cos(k[i - 1][0] + (k[i][0] - k[i - 1][0])/2)*dxy);
				dirs[i - 1].setY(uavs[0].getY() + sin(k[i - 1][0] + (k[i][0] - k[i - 1][0])/2)*dxy); 
			}
			while (calcAims(k[i - 1][0], k[i - 1][1], k[i][0], k[i][1], dirs[i - 1]) > aimsInSector + 1)
			{
				k[i].setK(k[i][0] - pi/180);
				k[i].setB(uavs[0].getY() - uavs[0].getX()*tan(k[i][0]));
				dirs[i - 1].setX(uavs[0].getX() + cos(k[i - 1][0] + (k[i][0] - k[i - 1][0])/2)*dxy);
				dirs[i - 1].setY(uavs[0].getY() + sin(k[i - 1][0] + (k[i][0] - k[i - 1][0])/2)*dxy); 
			}
		}
		dirs.push_back(Object(uavs[0].getX() + cos(k[uavs.size() - 1][0] + (2*pi - k[uavs.size() - 1][0])/2)*dxy, uavs[0].getY() + sin(k[uavs.size() - 1][0] + (2*pi - k[uavs.size() - 1][0])/2)*dxy));
		for (int i = 0; i < uavs.size() - 1; i++)
		{
			cout << '\n' << "UAV " << i << ":" << '\n';
			uavs[i].roat(aimsForUAV(k[i][0], k[i][1], k[i + 1][0], k[i + 1][1], dirs[i]));
			//uavs[i].elaborateRoat(goForUAV(k[i][0], k[i][1], k[i + 1][0], k[i + 1][1], dirs[i]));
		}
		cout << '\n' << "UAV " << uavs.size() - 1 << ":" << '\n';
		uavs[uavs.size() - 1].roat(aimsForUAV(k[uavs.size() - 1][0], k[uavs.size() - 1][1], 2*pi + k[0][0], k[0][1], dirs[uavs.size() - 1]));
		//uavs[i].elaborateRoat(goForUAV(k[i][0], k[i][1], k[i + 1][0], k[i + 1][1], dirs[i]));
	}
	else
	{
	}
};
bool Map::allUVAtogether()
{
	float sum = 0;
	for (int i = 0; i < uavs.size() - 1; i++)
		sum += uavs[i].getX() - uavs[i + 1].getX() + uavs[i].getY() - uavs[i + 1].getY();
	if (sum < ((x1 + x2)/100 + (y1 + y2)/100)*uavs.size())
		return true;
	return false;
};
int Map::calcAims(float k1, float b1, float k2, float b2, Object dir)
{
	int sum = 0;
	float x13, x23, y13, y23;
	Object centr((b2 - b1)/(tan(k1) - tan(k2)), tan(k1)*(b2 - b1)/(tan(k1) - tan(k2)) + b1);
	for (int i = 0; i < aims.size(); i++)
	{
		x13 = (aims[i].getY() - aims[i].getX()*(dir.getY() - aims[i].getY())/(dir.getX() - aims[i].getX()) - b1)/(tan(k1) - (dir.getY() - aims[i].getY())/(dir.getX() - aims[i].getX()));
		x23 = (aims[i].getY() - aims[i].getX()*(dir.getY() - aims[i].getY())/(dir.getX() - aims[i].getX()) - b2)/(tan(k2) - (dir.getY() - aims[i].getY())/(dir.getX() - aims[i].getX()));
		y13 = tan(k1)*x13 + b1;
		y23 = tan(k2)*x23 + b2;
		if ((y13 <= min(aims[i].getY(), dir.getY()) || y13 >= max(aims[i].getY(), dir.getY())) && (y23 <= min(aims[i].getY(), dir.getY()) || y23 >= max(aims[i].getY(), dir.getY())) && (x13 <= min(aims[i].getX(), dir.getX()) || x13 >= max(aims[i].getX(), dir.getX())) && (x23 <= min(aims[i].getX(), dir.getX()) || x23 >= max(aims[i].getX(), dir.getX())))
			sum++;
	}
	return sum;
};
vector<Aim> Map::aimsForUAV(float k1, float b1, float k2, float b2, Object dir)
{
	vector<Aim> sum;
	float x13, x23, y13, y23;
	Object centr((b2 - b1)/(tan(k1) - tan(k2)), tan(k1)*(b2 - b1)/(tan(k1) - tan(k2)) + b1);
	for (int i = 0; i < aims.size(); i++)
	{
		x13 = (aims[i].getY() - aims[i].getX()*(dir.getY() - aims[i].getY())/(dir.getX() - aims[i].getX()) - b1)/(tan(k1) - (dir.getY() - aims[i].getY())/(dir.getX() - aims[i].getX()));
		x23 = (aims[i].getY() - aims[i].getX()*(dir.getY() - aims[i].getY())/(dir.getX() - aims[i].getX()) - b2)/(tan(k2) - (dir.getY() - aims[i].getY())/(dir.getX() - aims[i].getX()));
		y13 = tan(k1)*x13 + b1;
		y23 = tan(k2)*x23 + b2;
		if ((y13 <= min(aims[i].getY(), dir.getY()) || y13 >= max(aims[i].getY(), dir.getY())) && (y23 <= min(aims[i].getY(), dir.getY()) || y23 >= max(aims[i].getY(), dir.getY())) && (x13 <= min(aims[i].getX(), dir.getX()) || x13 >= max(aims[i].getX(), dir.getX())) && (x23 <= min(aims[i].getX(), dir.getX()) || x23 >= max(aims[i].getX(), dir.getX())))
			sum.push_back(aims[i]);
	}
	return sum;
};
vector<GeoObject> Map::goForUAV(float k1, float b1, float k2, float b2, Object dir)
{
	vector<GeoObject> sum;
	float x13, x23, y13, y23;
	Object centr((b2 - b1)/(tan(k1) - tan(k2)), tan(k1)*(b2 - b1)/(tan(k1) - tan(k2)) + b1);
	for (int i = 0; i < objects.size(); i++)
	{
		x13 = (objects[i].getY() - objects[i].getX()*(dir.getY() - objects[i].getY())/(dir.getX() - objects[i].getX()) - b1)/(tan(k1) - (dir.getY() - objects[i].getY())/(dir.getX() - objects[i].getX()));
		x23 = (objects[i].getY() - objects[i].getX()*(dir.getY() - objects[i].getY())/(dir.getX() - objects[i].getX()) - b2)/(tan(k2) - (dir.getY() - objects[i].getY())/(dir.getX() - objects[i].getX()));
		y13 = tan(k1)*x13 + b1;
		y23 = tan(k2)*x23 + b2;
		if ((y13 <= min(objects[i].getY(), dir.getY()) || y13 >= max(objects[i].getY(), dir.getY())) && (y23 <= min(objects[i].getY(), dir.getY()) || y23 >= max(objects[i].getY(), dir.getY())) && (x13 <= min(objects[i].getX(), dir.getX()) || x13 >= max(objects[i].getX(), dir.getX())) && (x23 <= min(objects[i].getX(), dir.getX()) || x23 >= max(objects[i].getX(), dir.getX())))
			sum.push_back(objects[i]);
	}
	return sum;
};




