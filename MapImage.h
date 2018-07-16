#include "Image.h"
#include "ImageForPNM.h"
#include "ImageForQt.h"
#include "Map.h"
#include "src/interpolation.h"

class MapImage
{
	Map *map;
	Image *image;
public:
	MapImage(float nx1, float nx2, float ny1, float ny2);
	MapImage(Map &m);
    void setQImage(QImage *qimage);
	void loadFile(string file);
    Object coordinateToPoint(Object a);
    Object coordinateToPoint(float x, float y);
    void paintLine(vector<Object> objects, int color[3]);
    void paintLine(vector<Object> objects, std::string color = "red");
    void paintObjects(vector<GeoObject> objects, int color[3]);
    void paintObjects(vector<GeoObject> objects, std::string color = "black");
	void paintSpline(vector<Object> objects, int color = 0, bool cap = true);
    void paintPointX(int x, int y);
    void paintPointY(int x, int y);
	void paintSqare(int x, int y, int size = 5, int color = 0);
    void paintAims(vector<Aim> aims, int color[3]);
    void paintAims(vector<Aim> aims, std::string color = "red");
	void print(string file);
	void paintAll(int a, int b, int c);
};
