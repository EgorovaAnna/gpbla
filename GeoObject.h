#ifndef GeoObject_h
#define GeoObject_h
#include "Object.h"

class GeoObject: public Object //переопределить isPVO как false
{
protected:
	double radius;
    Object angles[4];
    int type;
public:
	GeoObject(double nx, double ny, double nr, bool npvo = false);  // сначала вызвать конструктор родительского! мб сюда передавать false?
    GeoObject(double nx1, double ny1, double nx2, double ny2, double nx3, double ny3, double nx4, double ny4, bool npvo = false);
	bool onWay(double x1, double y1, double x2, double y2); //проверка, проходит ли прямая между двумя точками через объект
	Object point(double x1, double y1, double x2, double y2); //возвращает оптимальную точку для облёта
	bool operator==(GeoObject go2);
	double getRadius();
    bool isRound();
    Object getAngles(int a);
};

#endif
