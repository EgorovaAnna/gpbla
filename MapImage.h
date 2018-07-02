#include "Image.h"
#include "Map.h"
#include "src/interpolation.h"
#include <QImage>

class MapImage
{
	Map *map;
	Image *image;
public:
	MapImage(float nx1, float nx2, float ny1, float ny2);
	MapImage(Map &m);
	void setImage(int x, int y);
	void loadFile(string file);
	Object coordinateToPoint(Object a, int color = 0);
	Object coordinateToPoint(float x, float y, int color = 0);
	void paintLine(vector<Object> objects, int color = 0);
	void paintLine(vector<Object> objects, QImage &im, QColor color);
	void drawLine(int x1, int y1, int x2, int y2, QImage &im, QColor color);
	void paintObjects(vector<GeoObject> objects, int color = 0);
	void paintSpline(vector<Object> objects, int color = 0, bool cap = true);
	void paintPointX(int x, int y, int color);
	void paintPointY(int x, int y, int color);
	void paintSqare(int x, int y, int size = 5, int color = 0);
	void paintAims(vector<Aim> aims);
	void print(string file);
	void paintAll(int a, int b, int c);
};
