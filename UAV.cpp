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
	int i, j, max = pow(10, 10);
	float **mas = new float*[aims.size() + 1], **mas2 = new float*[aims.size() + 1]; // матрица растояний
	float *g = new float[aims.size() + 1], *h = new float[aims.size() + 1];
	float min1, min2, mark[3], minel1, minel2;
	vector<int[2]> answer;
	for(i = 0; i <= aims.size(); i++)
	{
		mas[i] = new float[aims.size() + 1];
		mas2[i] = new float[aims.size() + 1];
	}
	for(i = 1; i <= aims.size(); i++)
	{
		min1 = max;
		for(j = 1; j <= aims.size(); j++)
		{
			if (i != j)
				mas[i][j] = pow(pow(aims[i].getX() - aims[j].getX(), 2) + pow(aims[i].getY() - aims[j].getY(), 2), 0.5);
				//cout << mas[i][j] = pow(pow(aims[i].getX() - aims[j].getX(), 2) + pow(aims[i].getY() - aims[j].getY(), 2), 0.5) << " ";
			else
				mas[i][j] = max;
			min1 = min(min1, mas[i][j]);
			mas2[i][j] = mas[i][j];
		}
		g[i] = min1;
		//cout << '\n';
	}
	mas[0][0] = max;
	mas2[0][0] = max; 
	min1 = max; min2 = max; 
	for(i = 1; i <= aims.size(); i++)
	{
		mas[i][0] = pow(pow(x - aims[i].getX(), 2) + pow(y - aims[i].getY(), 2), 0.5);
		mas[0][i] = pow(pow(x - aims[i].getX(), 2) + pow(y - aims[i].getY(), 2), 0.5);
		mas2[0][i] = mas[0][i];
		mas2[i][0] = mas[i][0];
		min1 = min(min1, mas[0][i]);
		min2 = min(min1, mas[i][0]);
	}
	g[0] = min1;
	h[0] = min2;
	for (int k = 0; k <= aims.size(); k++)
	{
		for(i = 0; i <= aims.size(); i++)
		{
			min2 = max;
			for(j = 0; j <= aims.size(); j++)
				mas2[i][j] -= g[i];
			for(j = 1; j <= aims.size(); j++)
				min2 = min(min2, mas[j][i]);
			h[i] = min2;
		}
		mark[0] = 0; milel1 = max; minel2 = max;
		for(i = 0; i <= aims.size(); i++)
			for(j = 0; j <= aims.size(); j++)
				mas2[i][j] -= h[j];
		for(i = 0; i <= aims.size(); i++)
			for(j = 0; j <= aims.size(); j++)
				if (mas2[i][j] == 0)
				{
					for (int d = 0; g <= aims.size(); d++)
					{
						if (mas2[i][d] < minel1 && d != j)
							minel1 = mas2[i][d];
						if (mas2[d][j] < minel2 && d != i)
							minel2 = mas2[d][j];
					}
					if (mark < minel1 + minel2)
					{
						mark[0] = minel1 + minel2;
						mark[1] = i; mark[2] = j;
					}
				}
		answer.push_back({mark[1], mark[2]});
		mas2[mark[2]][mark[1]] = max;
	}
	
};
void UAV::elaborateRoat(vector<GeoObject> objects)
{
};
