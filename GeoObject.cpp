#include "GeoObject.h"

GeoObject::GeoObject(float nx, float ny, float nr, bool npvo) : Object(nx, ny, npvo)
{
	radius = nr;
};
bool GeoObject::onWay(float x1, float y1, float x2, float y2)
{
	if (x1 == x2)
	{
		if (fabs(x1 - x) <= radius && y >= min(y1, y2) && y <= max(y1, y2))
			return true;
		return false;
	}
	if ((x >= min(x1, x2) && x <= max(x1, x2) && y >= min(y1, y2) && y <= max(y1, y2)) || fabs(x - x2) <= radius || fabs(y - y2) <= radius)
	{
		//попадает в прямоугольник. может, использовать его в начале поиска оптимальной точки, а не снаружи?
		float k = (y2 - y1)/(x2 - x1);
		float b = y1 - x1*(y2 - y1)/(x2 - x1);
		float d = (pow((2*k*b - 2*x - 2*y*k), 2) - (4 + 4*k*k)*(b*b - radius*radius + x*x + y*y - 2*y*b));   
		if(d < 0) 
			return false;
		return true;
	}
	return false;
};
Object GeoObject::point(float x1, float y1, float x2, float y2)
{
	if (abs(x1 - x2) <= abs(y1 - y2)/100)
	{
		if (x1 - x >= 0)
			return Object(x + radius*6.0/5.0, y);
		return Object(x - radius*6.0/5.0, y);
	}
	if (abs(y1 - y2) <= abs(x1 - x2)/100)
	{
		if (y1 - y >= 0)
			return Object(x, y + radius*6.0/5.0);
		return Object(x, y - radius*6.0/5.0);
	}
	float k = (y2 - y1)/(x2 - x1);
	float b = y1 - x1*(y2 - y1)/(x2 - x1);
	float d = pow((2*k*b - 2*x - 2*y*k), 2) - (4 + 4*k*k)*(b*b - radius*radius + x*x + y*y - 2*y*b);
	float x1cross = ((-(2*k*b - 2*x - 2*y*k) - sqrt(d))/(2 + 2*k*k)), x2cross = ((-(2*k*b - 2*x - 2*y*k) + sqrt(d))/(2 + 2*k*k)); 
	float y1cross = k*x1cross + b, y2cross = k*x2cross + b;
	float xcentre = (x1cross + x2cross)/2, ycentre = k*xcentre + b;
	//cout << xcentre << " " << ycentre << '\n';
	/*if (xcentre == x)
	{
		if (ycentre == y)
	}
	k = (ycentre - y)/(xcentre - x);
	b = y - x*(ycentre - y)/(xcentre - x);*/
	k = - 1/k;
	b = ycentre - k*xcentre;
	d = (pow((2*k*b - 2*x - 2*y*k), 2) - (4 + 4*k*k)*(b*b - (radius*6.0/5.0)*(radius*6.0/5.0) + x*x + y*y - 2*y*b));
	x1cross = ((-(2*k*b - 2*x - 2*y*k) - sqrt(d))/(2 + 2*k*k));     
	x2cross = ((-(2*k*b - 2*x - 2*y*k) + sqrt(d))/(2 + 2*k*k));
	y1cross = k*x1cross + b;     
	y2cross = k*x2cross + b;
	if ((x1cross - xcentre)*(x1cross - xcentre) + (y1cross - ycentre)*(y1cross - ycentre) < (x2cross - xcentre)*(x2cross - xcentre) + (y2cross - ycentre)*(y2cross - ycentre))
		return Object(x1cross, y1cross);
	else
		return Object(x2cross, y2cross);
};
bool GeoObject::operator==(GeoObject go2)
{
	if (go2.getX() == x && go2.getY() == y)
		return true;
	return false;
};
float GeoObject::getRadius()
{
	return radius;
};

