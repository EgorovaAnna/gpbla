#include "UAV.h"
#include <unistd.h>
#include "src/proto/RouteData.pb.h"

class Map
{
	float x1, x2, y1, y2; //координаты верхнего левого и нижнего правого углов
	vector<GeoObject> objects; //препятствия и ПВО
	vector<Aim> aims;
	vector<UAV> uavs;
	vector<Line> k;
public:
    Map();
    Map(float nx1, float nx2, float ny1, float ny2); //первичная инициализация
    void sortXY();
    float& operator[](int a);
	vector<UAV> getUAV();
	vector<GeoObject> getO();
	vector<Aim> getA();
	vector<Line> getK();
	void addObject(GeoObject newGO); 
	void addAim(Aim newAim);
	void addUAV(UAV nemUAV);
    void sortAims(Object centre);
	void readGIS(string file); //у меня где-то есть работа с этим форматом
	void divideTer();//разделение территории, каждому бла назначаются цели и передается вектор объектов на его территоррии (???)
	bool allUVAtogether();//возвращает true, если все бла рядом
	int calcAims(float k1, float b1, float k2, float b2, Object dir); // подсчет количества целей между двумя прямыми
	vector<Aim> aimsForUAV(float k1, float b1, float k2, float b2, Object dir);
	vector<GeoObject> goForUAV(float k1, float b1, float k2, float b2, Object dir);
    void createPBF(string filename);
};

