#ifndef OBJECT_H
#define OBJECT_H
#include "Object.h"

class Aim: public Object
{
public:
    Aim(double nx, double ny, double nz, bool npvo = false); // сначала вызвать конструктор родительского!
	bool operator ==(Aim a2);
};

#endif
