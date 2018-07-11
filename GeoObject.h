#ifndef GeoObject_h
#define GeoObject_h
#include "Object.h"

class GeoObject: public Object //переопределить isPVO как false
{
protected:
	float radius;
    Object angles[4];
    int type;
public:
	GeoObject(float nx, float ny, float nr, bool npvo = false);  // сначала вызвать конструктор родительского! мб сюда передавать false?
    GeoObject(float nx1, float ny1, float nx2, float ny2, float nx3, float ny3, float nx4, float ny4, bool npvo = false);
	bool onWay(float x1, float y1, float x2, float y2); //проверка, проходит ли прямая между двумя точками через объект
	Object point(float x1, float y1, float x2, float y2); //возвращает оптимальную точку для облёта
	bool operator==(GeoObject go2);
	float getRadius();
    bool isRound();
    Object getAngles(int a);
};

#endif
