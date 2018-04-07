#include "Image.h"
#include "Map.h"

class MapImage
{
	Map *map;
	Image *image;
public:
	MapImage(float nx1, float nx2, float ny1, float ny2);
	MapImage(Map &m);
	void loadFile(string file);
	Object coordinateToPoint(Object a, int color = 0);
	Object coordinateToPoint(float x, float y, int color = 0);
	void paintLine(vector<Object> objects, int color = 0);
	void paintObjects(vector<GeoObject> objects, int color = 0);
	void paintAims(vector<Aim> aims);
	void print(string file);
};
