#include "UAV.h"


UAV::UAV(float nx, float ny, float nz, int nt)
{
	x = nx;
	y = ny;
	z = nz;
	t = nt;
};
void UAV::addPoint(Object point)
{
	points.push_back(point);
}; 
void UAV::addAim(Aim newAim)
{
	aims.push_back(newAim);
};
void UAV::iteration(float dt)
{
	
}; 
void UAV::deleteAim(Aim aim)
{
	for(auto i = aims.begin(); i < aims.end(); i++)
		if (*i == aim)
			aims.erase(i);
};
float UAV::getX()
{
	return x;
};
float UAV::getY()
{
	return y;
};
void UAV::roat(vector<Aim> aims)
{
	int i, j;
	float **mas = new float*[aims.size() + 1]; // матрица растояний
	for(i = 0; i <= aims.size(); i++)
		mas[i] = new float[aims.size() + 1];
	for(i = 1; i <= aims.size(); i++)
	{
		for(j = 1; j <= aims.size(); j++)
		{
			if (i != j)
				mas[i][j] = pow(pow(aims[i].getX() - aims[j].getX(), 2) + pow(aims[i].getY() - aims[j].getY(), 2), 0.5);
				//cout << mas[i][j] = pow(pow(aims[i].getX() - aims[j].getX(), 2) + pow(aims[i].getY() - aims[j].getY(), 2), 0.5) << " ";
			else
				mas[i][j] = pow(10, 10); //???
		}
		//cout << '\n';
	}
	mas[0][0] = pow(10, 10); //???
	for(i = 1; i <= aims.size(); i++)
	{
		mas[i][0] = pow(pow(x - aims[j].getX(), 2) + pow(y - aims[j].getY(), 2), 0.5);
		mas[0][i] = pow(pow(x - aims[j].getX(), 2) + pow(y - aims[j].getY(), 2), 0.5);
	}
};
void UAV::elaborateRoat(vector<GeoObject> objects)
{
};
