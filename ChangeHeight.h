#include "Object.h"

class ChangeHeight: public Object //это довольно странно, но нужно, чтобы было удобно хранить точки, которые облетает бла
{
	float height; //на какую высоту поднимаемся/снижаемся
public:
	ChangeHeight(float nx, float ny, float nh); // сначала вызвать конструктор родительского! 
	bool upper(float height); //вернет true, если мы поднимаемся, полагаю, что потребуется для рассчетов сплайна.
};