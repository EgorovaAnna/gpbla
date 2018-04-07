#ifndef GeoObject_h
#define GeoObject_h
#include "Object.h"

class GeoObject: public Object //переопределить isPVO как false
{
protected:
	float radius;
public:
	GeoObject(float nx, float ny, float nr, bool npvo = false);  // сначала вызвать конструктор родительского! мб сюда передавать false?
	bool onWay(float x1, float y1, float x2, float y2); //проверка, проходит ли прямая между двумя точками через объект
	Object point(float x1, float y1, float x2, float y2); //возвращает оптимальную точку для облёта
	bool operator==(GeoObject go2);
	float getRadius();
};

#endif
