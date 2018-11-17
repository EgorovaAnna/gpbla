#include "UAV.h"
#include <unistd.h>
//#include "src/proto/RouteData.pb.h"

class Map
{
    double x1, x2, y1, y2; //координаты верхнего левого и нижнего правого углов в метрах
    double x1d, x2d, y1d, y2d; //координаты верхнего левого и нижнего правого углов в градусах
	vector<GeoObject> objects; //препятствия и ПВО
	vector<Aim> aims;
	vector<UAV> uavs;
	vector<Line> k;
public:
    Map();
    Map(double nx1,double nx2, double ny, double ny2); //первичная инициализация
    void sortXY();
    double& operator[](int a);
	vector<UAV> getUAV();
	vector<GeoObject> getO();
	vector<Aim> getA();
    vector<UAV> getUAVdegree();
    vector<GeoObject> getOdegree();
    vector<Aim> getAdegree();
    vector<Line> getKdegree();
	void addObject(GeoObject newGO); 
    void restruct(); //пересохраняет координаты в градусах в метры
	void addAim(Aim newAim);
	void addUAV(UAV nemUAV);
    void sortAims(Object centre);
    vector<double>  sortUAV();
    void sortAims(Object centre, vector<double> rad);
    bool tangensGreater(Aim a, Aim b, Object centre);
    void resortAims(Object centre, int fromIndex, int number, vector<Aim> toInclude);
	void readGIS(string file); //у меня где-то есть работа с этим форматом
	void divideTer();//разделение территории, каждому бла назначаются цели и передается вектор объектов на его территоррии (???)
	bool allUVAtogether();//возвращает true, если все бла рядом
    void createPBF(string filename);
    template<typename T> T getDegree(T object);
};

