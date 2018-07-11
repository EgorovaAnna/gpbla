#include "Object.h"

class Aim: public Object
{
	float z; //для учета рельефа
public:
	Aim(float nx, float ny, float nz, bool npvo = false); // сначала вызвать конструктор родительского! 
    float getH();
	bool operator ==(Aim a2);
};
