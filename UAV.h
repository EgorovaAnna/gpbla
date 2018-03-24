#include "Aim.h"
#include "PVO.h"
#include "ChangeHeight.h"

class UAV
{
	float x, y, z;
	int t; // текущее время
	float radioview; //радиовидимость
	float focus;
	float way; //запас хода (топлива?)
	vector<Object> points; //точки, через которые он должен пролететь
	vector<Aim> aims;
public:
	UAV(float nx, float ny, float nz, int nt); //первичная инициализация
	void addPoint(Object point); 
	void addAim(Aim newAim);
	void iteration(float dt); //моделирование полета
	void deleteAim(Aim aim); //когда цель кто-то отснял
	float getX();
	float getY();
	void roat(vector<Aim> aims); //метод ветвей и границ
	void elaborateRoat(vector<GeoObject> objects); //уточнение траекторий
};
