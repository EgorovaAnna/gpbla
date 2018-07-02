#include "Aim.h"
#include "PVO.h"
#include "ChangeHeight.h"
#include <unistd.h>
#include <algorithm>


class UAV
{
	float x, y, z;
	int t; // текущее время
	float radioview; //радиовидимость
	float focus; //фокусное расстояние
	float way; //запас хода (топлива?)
	float maxH; //максимальная высота
	float velocity; //скорость
	vector<Object> points; //точки, через которые он должен пролететь
	vector<Aim> aims;
public:
	UAV(float nx, float ny, float nz, int nt); //первичная инициализация
	void addPoint(Object point); 
	void addAim(Aim newAim);
	void iteration(float dt); //моделирование полета
	void deleteAim(Aim aim); //когда цель кто-то отснял
	void setR(float rad);
	void setF(float f);
	void setW(float w);
	void setH(float h);
	void setV(float v);
	float getX();
	float getY();
	float getR();
	float getF();
	float getW();
	float getH();
	float getV();
	void roat(vector<Aim> aims); //метод ветвей и границ
	void elaborateRoat(vector<GeoObject> objects); //уточнение траекторий
	vector<Object> getRoat();
};

