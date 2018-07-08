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
void MapImage::setImage(int x, int y)
{
	int tsize[2] = {x, y};
	image = new Image(tsize);
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
	int x1, x2, y1, y2;
	for (int i = 0; i < objects.size(); i++)
		points.push_back(coordinateToPoint(objects[i]));
	for (int i = 0; i < objects.size() - 1; i++)
	{
		x1 = points[i].getX();
		y1 = points[i].getY();
		x2 = points[i + 1].getX();
		y2 = points[i + 1].getY();
		image -> drawLine(x1, y1, x2, y2, color);
		image -> drawLine(x1 - (x1 == 0 ? 0 : 1), y1, x2 - (x2 == 0 ? 0 : 1), y2, color);
		image -> drawLine(x1, y1 + (y1 == image -> getY() ? 0 : 1), x2, y2 + (y2 == image -> getY() ? 0 : 1), color);
		for (int j = -1; j > -5; j--)
		{
			if (y1 - j >= 0 && y2 - j >= 0)
				image -> drawLine(x1, y1 - j, x2, y2 - j, color);
			else
				image -> drawLine(x1, y1 + 5 - j, x2, y2 + 5 - j, color);
			if (x1 - j >= 0 && x2 - j >= 0)
				image -> drawLine(x1 -j, y1, x2 - j, y2, color);
			else
				image -> drawLine(x1 + 5 - j, y1, x2 + 5 - j, y2, color);
		}
	}
}
void MapImage::paintLine(vector<Object> objects, QImage &im, QColor color)
{
	vector<Object> points;
	int x1, x2, y1, y2;
	for (int i = 0; i < objects.size(); i++)
		points.push_back(coordinateToPoint(objects[i]));
	for (int i = 0; i < objects.size() - 1; i++)
	{
		x1 = points[i].getX();
		y1 = points[i].getY();
		x2 = points[i + 1].getX();
		y2 = points[i + 1].getY();
		drawLine(x1, y1, x2, y2, im, color);
		drawLine(x1 - (x1 == 0 ? 0 : 1), y1, x2 - (x2 == 0 ? 0 : 1), y2, im, color);
		drawLine(x1, y1 + (y1 == image -> getY() ? 0 : 1), x2, y2 + (y2 == image -> getY() ? 0 : 1), im, color);
		for (int j = -1; j > -5; j--)
		{
			if (y1 - j >= 0 && y2 - j >= 0)
				drawLine(x1, y1 - j, x2, y2 - j, im, color);
			else
				drawLine(x1, y1 + 5 - j, x2, y2 + 5 - j, im, color);
			if (x1 - j >= 0 && x2 - j >= 0)
				drawLine(x1 -j, y1, x2 - j, y2, im, color);
			else
				drawLine(x1 + 5 - j, y1, x2 + 5 - j, y2, im, color);
		}
	}
}
void MapImage::drawLine(int x1, int y1, int x2, int y2, QImage &im, QColor color)
{
	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	int i;
	if (x1 == x2||y1 == y2)
	{
		if (x1 == x2)
		{
			for (i = y1; i!= y2; i = i + signY)
				im.setPixelColor(x1, i, color);
		}
		if(y1 == y2)
		{
			for (i = x1; i!= x2; i = i + signX)
				im.setPixelColor(i, y1, color);
		}
	}
	else
	{
		im.setPixelColor(x2, y2, color);	
		while(x1 != x2 || y1 != y2)
		{
			im.setPixelColor(x1, y1, color);
			int error2 = error*2;
			if (error2 > -deltaY)
			{
				error -= deltaY;
				x1 += signX;
			}
			if (error2 < deltaX)
			{
				error += deltaX;
				y1 += signY;
			}
		}
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
void MapImage::paintObjects(vector<GeoObject> objects, QImage &im, QColor color)
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
					im.setPixelColor(j, k, color);
}
/*void MapImage::paintSpline(vector<Object> objects, int color, bool cap)
{
	alglib::spline1dinterpolant s1, s2;
	int minxy = image -> getX(), maxxy = 0, imin, imax, signal = 0, i, j = -1, k, l, bufx, bufy;
	float countkb[3];
	vector<Object> points;
	alglib::real_1d_array x1, x2, y1, y2;
	double *dx1, *dx2, *dy1, *dy2;
	for (i = 0; i < objects.size() - 1; i++)
	{
		j++;
		points.push_back(coordinateToPoint(objects[i]));
		if(points[j].getX() < minxy)
		{
			minxy = points[j].getX();
			imin = j;
		}
		if(points[j].getX() > maxxy)
		{
			maxxy = points[j].getX();
			imax = j;
		}
		if (cap)
		{
			k = coordinateToPoint(objects[i + 1]).getX();
			l = coordinateToPoint(objects[i + 1]).getY();
			countkb[0] = min(abs(points[j].getX() - k)/5.0, (image -> getX())/200.0);
			countkb[1] = (l - points[j].getY())/(k - points[j].getX());
			countkb[2] = - points[j].getX()*countkb[1] + points[j].getY();
			while (points[j].distanceXY((float)k, (float)l) > 2*countkb[0])
			{
				cout << points[j].getX() << "__" << points[j].getY() << '\n';
				bufx = points[j].getX() + countkb[0]; bufy = countkb[1]*bufx + countkb[2];
				if((l - bufy)*(bufy - points[j].getY()) > 0 && (k - bufx)*(bufx - points[j].getX()) > 0)
				{
					j++;
					points.push_back(Object(bufx, bufy));
				}
				else
					break;
			}
		}
	}
	for (i = min(imin, imax) + 1; i < max(imin, imax); i++)
	{
		j = (i + abs(imin - imax))%(points.size());
		k = j - 1;
		l = j + 1;
		if (j == 0)
			k = points.size() - 1;
		if (j == points.size() - 1)
			l = 0;
		if ((points[i].getX() - points[i - 1].getX())*(points[i + 1].getX() - points[i].getX()) < 0)
			signal = -1;
	}
	for (j = 0; j < min(imin, imax); j++)
	{
		k = j - 1;
		l = j + 1;
		if (j == 0)
			k = points.size() - 1;
		if ((points[j].getX() - points[k].getX())*(points[l].getX() - points[j].getX()) < 0)
			signal = -1;
	}
	for (j = max(imin, imax) + 1; j < points.size(); j++)
	{
		k = j - 1;
		l = j + 1;
		if (j == points.size() - 1)
			l = 0;
		if ((points[j].getX() - points[k].getX())*(points[l].getX() - points[j].getX()) < 0)
			signal = -1;
	}
	if (signal == 0)
	{
		dx1 = new double[abs(imin - imax) + 1];
		dy1 = new double[abs(imin - imax) + 1];
		dx2 = new double[points.size() - abs(imin - imax) + 1];
		dy2 = new double[points.size() - abs(imin - imax) + 1];
		for (i = min(imin, imax); i <= max(imin, imax); i++)
		{
			dx1[i - min(imin, imax)] = points[i].getX();
			dy1[i - min(imin, imax)] = points[i].getY();
			cout << i << " = " << dx1[i - min(imin, imax)] << "  " << dy1[i - min(imin, imax)] << " ; ";
		}
		cout << '\n';
		for (j = 0; j <= min(imin, imax); j++)
		{
			i = min(imin, imax) - j;
			dx2[i] = points[j].getX();
			dy2[i] = points[j].getY();
			cout << i << " = " << dx2[i] << "  " << dy2[i] << " ; ";
		}
		for (j = points.size() - 1 ; j >= max(imin, imax); j--)
		{
			i++;
			dx2[i] = points[j].getX();
			dy2[i] = points[j].getY();
			cout << i << " = " << dx2[i] << "  " << dy2[i] << " ; ";
		}
		cout << '\n' << '\n';
		x1.setcontent(abs(imin - imax) + 1, dx1);
		y1.setcontent(abs(imin - imax) + 1, dy1);
		x2.setcontent(points.size() - abs(imin - imax) + 1, dx2);
		y2.setcontent(points.size() - abs(imin - imax) + 1, dy2);
		alglib::spline1dbuildcubic(x1, y1, s1);
		alglib::spline1dbuildcubic(x2, y2, s2);
		for (i = minxy; i < maxxy; i++)
		{
			paintPointX(i, (int)spline1dcalc(s1, i), color);
			if (cap)
				paintPointX(i, (int)spline1dcalc(s2, i), color);
		}
	}
	else
	{
		minxy = image -> getY(), maxxy = 0;
		for (i = 0; i < points.size(); i++)
		{
			if(points[i].getY() < minxy)
			{
				minxy = points[i].getY();
				imin = i;
			}
			if(points[i].getY() > maxxy)
			{
				maxxy = points[i].getY();
				imax = i;
			}
		}
		dx1 = new double[abs(imin - imax) + 1];
		dy1 = new double[abs(imin - imax) + 1];
		dx2 = new double[points.size() - abs(imin - imax) + 1];
		dy2 = new double[points.size() - abs(imin - imax) + 1];
		for (i = min(imin, imax); i <= max(imin, imax); i++)
		{
			dx1[i - min(imin, imax)] = points[i].getX();
			dy1[i - min(imin, imax)] = points[i].getY();
			cout << i << " = " <<  dx1[i - min(imin, imax)] << "  " << dy1[i - min(imin, imax)] << " ; ";
		}
		cout << '\n';
		for (j = 0; j <= min(imin, imax); j++)
		{
			i = min(imin, imax) - j;
			dx2[i] = points[j].getX();
			dy2[i] = points[j].getY();
			cout << i << " = " << dx2[i] << "  " << dy2[i] << " ; ";
		}
		for (j = points.size() - 1 ; j >= max(imin, imax); j--)
		{
			i++;
			dx2[i] = points[j].getX();
			dy2[i] = points[j].getY();
			cout << i << " = " << dx2[i] << "  " << dy2[i] << " ; ";
		}
		cout << '\n' << '\n';
		x1.setcontent(abs(imin - imax) + 1, dx1);
		y1.setcontent(abs(imin - imax) + 1, dy1);
		x2.setcontent(points.size() - abs(imin - imax) + 1, dx2);
		y2.setcontent(points.size() - abs(imin - imax) + 1, dy2);
		alglib::spline1dbuildcubic(y1, x1, s1);
		alglib::spline1dbuildcubic(y2, x2, s2);
		for (i = minxy; i < maxxy; i++)
		{
			paintPointX((int)spline1dcalc(s1, i), i, color);
			paintPointX((int)spline1dcalc(s2, i), i, color);
		}
	}
}*/
void MapImage::paintAims(vector<Aim> aims, QImage &im, QColor color)
{
	vector<Object> points;
    int rad = 20;
	for (int i = 0; i < aims.size(); i++)
		points.push_back(coordinateToPoint(aims[i]));
	for (int i = 0; i < aims.size(); i++)
		for (int j = max((int)points[i].getX() - rad, 0); j <= min((int)points[i].getX() + rad, image -> getX()); j++)
			for (int k = max((int)points[i].getY() - rad, 0); k <= min((int)points[i].getY() + rad, image -> getY()); k++)
				if (points[i].distanceXY(j, k) <= rad)
					im.setPixelColor(j, k, color);
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
void MapImage::paintPointX(int x, int y, int color)
{
	//int rad = 3, color3[3] = {((color == 0) ? 255 : color), 0, 0};
	int rad = 3, color3[3] = {0, 0, 0};
	for (int k = max(y - rad, 0); k <= min(y + rad, image -> getY()); k++)
		image -> drawPoint(x, k, color3);
	for (int k = max(y - rad, 0); k <= min(y + rad, image -> getY()); k++)
		image -> drawPoint(x + 1, k, color3);
	for (int k = max(y - rad, 0); k <= min(y + rad, image -> getY()); k++)
		image -> drawPoint(x - 1, k, color3);
}
void MapImage::paintPointY(int x, int y, int color)
{
	//int rad = 3, color3[3] = {((color == 0) ? 255 : color), 0, 0};
	int rad = 3, color3[3] = {0, 0, 0};
	for (int k = max(x - rad, 0); k <= min(x + rad, image -> getX()); k++)
		image -> drawPoint(k, y, color3);
	for (int k = max(x - rad, 0); k <= min(x + rad, image -> getX()); k++)
		image -> drawPoint(k, y + 1, color3);
	for (int k = max(x - rad, 0); k <= min(x + rad, image -> getX()); k++)
		image -> drawPoint(k, y - 1, color3);
}
void MapImage::paintSqare(int x, int y, int size, int color)
{
	int color3[3] = {0, 0, 0};
	for (int k = max(x - size, 0); k <= min(x + size, image -> getX()); k++)
		for (int j = max(y - size, 0); j <= min(y + size, image -> getY()); j++)
			image -> drawPoint(k, j, color3);
}
void MapImage::paintAll(int a, int b, int c)
{
	image -> paintAll(a, b, c);
}
void MapImage::print(string file)
{
	image -> showFile(file);
}

