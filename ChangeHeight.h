#include "Object.h"
#include "GeoObject.h"
#include "Aim.h"

class ChangeHeight: public Object //это довольно странно, но нужно, чтобы было удобно хранить точки, которые облетает бла
{
    double height;
public:
    ChangeHeight();
    ChangeHeight(Aim aim);
    ChangeHeight(Object o);
    ChangeHeight(double nx, double ny, double nh, bool npvo = false); // сначала вызвать конструктор родительского!
    bool upper(double h); //вернет true, если мы поднимаемся, полагаю, что потребуется для рассчетов сплайна.
    void operator=(Aim aim);
    void operator=(GeoObject go);
    void operator=(Object o);
};
