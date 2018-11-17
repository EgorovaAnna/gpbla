#include "GeoObject.h"

GeoObject::GeoObject(double nx, double ny, double nr, bool npvo) : Object(nx, ny, npvo)
{
	radius = nr;
    type = 0;
};
GeoObject::GeoObject(double nx1, double ny1, double nx2, double ny2, double nx3, double ny3, double nx4, double ny4, bool npvo) : Object((nx1 + nx2 + nx3 + nx4)/4, (ny1 + ny2 + ny3 + ny4)/4, npvo)
{
     vector<Object> angle1, angle2;
     angles[0].setX(nx1);
     angles[0].setY(ny1);
     angles[1].setX(nx2);
     angles[1].setY(ny2);
     angles[2].setX(nx3);
     angles[2].setY(ny3);
     angles[3].setX(nx4);
     angles[3].setY(ny4);
     for (int i = 0; i < 4; i++)
         angle1.push_back(angles[i]);
     for (int i = 0; i < 4; i++)
     {
         if (angle1[i].getX() > x)
             angle2.insert(angle2.begin(), angle1[i]);
         else
             angle2.push_back(angle1[i]);
     }
     angle1 = angle2;
     for (int i = 0; i < 3; i++)
         for (int j = i + 1; j < 4; j++)
         {
             if (angle1[i].getX() > x && angle1[j].getX() > x)
             {
                 if (angle1[i].getY() < angle1[j].getY())
                 {
                     angle2[i] = angle1[j];
                     angle2[j] = angle1[i];
                 }
             }
             if (angle1[i].getX() < x)
             {
                 if (angle1[i].getY() > angle1[j].getY())
                 {
                     angle2[i] = angle1[j];
                     angle2[j] = angle1[i];
                 }
             }
         }
     for (int i = 0; i < 4; i++)
         angles[i] = angle2[i];
     type = 1;
     radius = max(distance(angles[0]), distance(angles[1]));
     radius = max(radius, distance(angles[2]));
     radius = max(radius, distance(angles[3]));
};
bool GeoObject::onWay(double x1, double y1, double x2, double y2)
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
        double k = (y2 - y1)/(x2 - x1);
        double b = y1 - x1*(y2 - y1)/(x2 - x1);
        double d = (pow((2*k*b - 2*x - 2*y*k), 2) - (4 + 4*k*k)*(b*b - radius*radius + x*x + y*y - 2*y*b));
		if(d < 0) 
			return false;
		return true;
	}
	return false;
};
Object GeoObject::point(double x1, double y1, double x2, double y2)
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
    double k = (y2 - y1)/(x2 - x1);
    double b = y1 - x1*(y2 - y1)/(x2 - x1);
    double d = pow((2*k*b - 2*x - 2*y*k), 2) - (4 + 4*k*k)*(b*b - radius*radius + x*x + y*y - 2*y*b);
    double x1cross = ((-(2*k*b - 2*x - 2*y*k) - sqrt(d))/(2 + 2*k*k)), x2cross = ((-(2*k*b - 2*x - 2*y*k) + sqrt(d))/(2 + 2*k*k));
    double y1cross = k*x1cross + b, y2cross = k*x2cross + b;
    double xcentre = (x1cross + x2cross)/2, ycentre = k*xcentre + b;
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
double GeoObject::getRadius()
{
	return radius;
};
bool GeoObject::isRound()
{
    if (type == 0)
        return true;
    return false;
};
Object GeoObject::getAngles(int a)
{
    if (a >= 0 && a <= 4)
        return angles[a];
    else
        return Object(x, y);
};

