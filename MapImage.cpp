#include "MapImage.h"

MapImage::MapImage(float nx1, float nx2, float ny1, float ny2)
{
	map = new Map(nx1, nx2, ny1, ny2);
}
MapImage::MapImage(Map &m)
{
	map = &m;
}
void MapImage::loadFile(string file)
{
	ifstream fin(file);
	string buf;
	int tsize[2];
	fin >> buf;
	fin >> tsize[0] >> tsize[1];
	fin >> buf;
	image = new Image(tsize);
	image -> loadIm(fin);
}
Object MapImage::coordinateToPoint(Object a, int color)
{
	return Object((int)(a.getX() - (*map)[0])*(image -> getX())/((*map)[1] - (*map)[0]), (int)(a.getY() - (*map)[2])*(image -> getY())/((*map)[3] - (*map)[2]), color);
}
Object MapImage::coordinateToPoint(float x, float y, int color)
{
	return Object((int)(x - (*map)[0])*(image -> getX())/((*map)[1] - (*map)[0]), (int)(y - (*map)[2])*(image -> getY())/((*map)[3] - (*map)[2]), color);
}
void MapImage::paintLine(vector<Object> objects, int color)
{
	vector<Object> points;
	for (int i = 0; i < objects.size(); i++)
		points.push_back(coordinateToPoint(objects[i]));
	for (int i = 0; i < objects.size() - 1; i++)
	{
		image -> drawLine(points[i].getX(), points[i].getY(), points[i + 1].getX(), points[i + 1].getY(), color);
		image -> drawLine(points[i].getX(), points[i].getY() - 1, points[i + 1].getX(), points[i + 1].getY() - 1, color);
		image -> drawLine(points[i].getX(), points[i].getY() + 1, points[i + 1].getX(), points[i + 1].getY() + 1, color);
		image -> drawLine(points[i].getX() - 1, points[i].getY(), points[i + 1].getX() - 1, points[i + 1].getY(), color);
		image -> drawLine(points[i].getX() + 1, points[i].getY(), points[i + 1].getX() + 1, points[i + 1].getY(), color);
	}
}
void MapImage::paintObjects(vector<GeoObject> objects, int color)
{
	vector<Object> points;
	vector<int> rad;
	for (int i = 0; i < objects.size(); i++)
	{
		points.push_back(coordinateToPoint(objects[i]));
		rad.push_back((int)(objects[i].getRadius()*(image -> getX())/((*map)[1] - (*map)[0])));
	}
	for (int i = 0; i < objects.size(); i++)
		for (int j = max((int)points[i].getX() - rad[i], 0); j <= min((int)points[i].getX() + rad[i], image -> getX()); j++)
			for (int k = max((int)points[i].getY() - rad[i], 0); k <= min((int)points[i].getY() + rad[i], image -> getY()); k++)
				if (points[i].distanceXY(j, k) <= rad[i])
					image -> drawPoint(j, k, color);
}
void MapImage::paintAims(vector<Aim> aims)
{
	vector<Object> points;
	int rad = 20, color[3] = {0, 255, 0};
	for (int i = 0; i < aims.size(); i++)
		points.push_back(coordinateToPoint(aims[i]));
	for (int i = 0; i < aims.size(); i++)
		for (int j = max((int)points[i].getX() - rad, 0); j <= min((int)points[i].getX() + rad, image -> getX()); j++)
			for (int k = max((int)points[i].getY() - rad, 0); k <= min((int)points[i].getY() + rad, image -> getY()); k++)
				if (points[i].distanceXY(j, k) <= rad)
					image -> drawPoint(j, k, color);
}
void MapImage::print(string file)
{
	image -> showFile(file);
}

