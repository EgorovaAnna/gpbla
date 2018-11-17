#include "GeoObject.h"

class PVO: public GeoObject //переопределить isPVO как true
{
	double p; //вероятность быть сбитым в этой области
public:
	PVO(double nx, double ny, double nr, double np); // сначала вызвать конструктор родительского!
	bool compile(double xuva, double yuva, double zuva); //возвращает true, если координаты попадают в полусферу и БЛА сбит с учетом вероятности
};
