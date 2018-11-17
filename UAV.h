#include "Aim.h"
#include "PVO.h"
#include "ChangeHeight.h"
#include <unistd.h>
#include <algorithm>


class UAV
{
    double x, y, z;
	int t; // текущее время
    double radioview; //радиовидимость
    double focus; //фокусное расстояние
    double way; //запас хода (топлива?)
    double maxH, flightAltitude; //максимальная высота, нормальная высота
    double velocity; //скорость
    double changingHeight; //скорость изменения высоты (угол снижения/подъема)
    vector<ChangeHeight> points; //точки, через которые он должен пролететь
	vector<Aim> aims;
public:
    UAV(double nx, double ny, double nz, double fA, double cH = 30.); //первичная инициализация
    UAV(double nx, double ny, double nz);
    UAV(){};
    void addPoint(ChangeHeight point);
	void addAim(Aim newAim);
    void iteration(double dt); //моделирование полета
	void deleteAim(Aim aim); //когда цель кто-то отснял
    void emptyRoats();
    void setR(double rad);
    void setF(double f);
    void setW(double w);
    void setH(double h);
    void setV(double v);
    void setX(double nx);
    void setY(double ny);
    double getX();
    double getY();
    double getR();
    double getF();
    double getW();
    double getH();
    double getV();
	void roat(vector<Aim> aims); //метод ветвей и границ
	void elaborateRoat(vector<GeoObject> objects); //уточнение траекторий
    void setRoat(vector<ChangeHeight> roating);
    vector<ChangeHeight> getRoat();
};

