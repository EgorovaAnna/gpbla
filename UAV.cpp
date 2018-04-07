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
	int i, j, aimssize = aims.size(), iter, k, max = (int)pow(10, 10);
	if (aimssize == 1 || aimssize == 2)
	{
		points.push_back(Object(x, y));
		points.push_back(aims[0]);
		if (aimssize == 2)
			points.push_back(aims[1]);
		points.push_back(Object(x, y));
	}
	else
	{
		float **mas = new float*[aimssize + 1], **mas2 = new float*[aimssize + 1]; // матрица растояний
		float *g = new float[aimssize + 1], *h = new float[aimssize + 1];
		float min1, min2, mark[3], minel1, minel2;
		vector<int> column, line;
		vector<int> from, to;
		for(i = 0; i <= aimssize; i++)
		{
			mas[i] = new float[aimssize + 1];
			mas2[i] = new float[aimssize + 1];
			column.push_back(i); line.push_back(i);
			cout << aims[i].getX() << "; " << aims[i].getY() << "       ";
		}
		cout << '\n' << '\n' << '\n';
		for(i = 1; i <= aimssize; i++)
		{
			min1 = max;
			for(j = 1; j <= aimssize; j++)
			{
				if (i != j)
					mas[i][j] = aims[i - 1].distance(aims[j - 1]); //pow(pow(aims[i - 1].getX() - aims[j - 1].getX(), 2) + pow(aims[i - 1].getY() - aims[j - 1].getY(), 2), 0.5);
				else
					mas[i][j] = max;
				min1 = min(min1, mas[i][j]);
				mas2[i][j] = mas[i][j];
			}
			g[i] = min1;
			mas[i][0] = pow(pow(x - aims[i - 1].getX(), 2) + pow(y - aims[i - 1].getY(), 2), 0.5);
			mas[0][i] = mas[i][0];
			mas2[0][i] = mas[0][i];
			mas2[i][0] = mas[i][0];
			g[0] = min(g[0], mas[0][i]);
			h[0] = min(h[0], mas[i][0]);
		}
		mas[0][0] = max;
		mas2[0][0] = max;	
		while (column.size() != 1)
		{
			iter = column.size();
			for(i = 0; i < iter; i++)
			{
				min1 = max;
				for(j = 0; j < iter; j++)
					min1 = min(min1, mas2[line[i]][column[j]]);
				g[line[i]] = min1;
				for(j = 0; j < iter; j++)
					mas2[line[i]][column[j]] -= g[line[i]];
			}
			for(i = 0; i < iter; i++)
			{
				min2 = max;
				for(j = 0; j < iter; j++)
					min2 = min(min2, mas2[line[j]][column[i]]);
				h[column[i]] = min2;
				for(j = 0; j < iter; j++)
					mas2[line[j]][column[i]] -= h[column[i]];
			}
			mark[0] = -1;
			for(i = 0; i < iter; i++)
				for(j = 0; j < iter; j++)
					if (mas2[line[i]][column[j]] == 0)
					{
						minel1 = max; minel2 = max;
						for (k = 0; k < iter; k++)
						{
							if (mas2[line[i]][column[k]] < minel1 && k != j)
								minel1 = mas2[line[i]][column[k]];
							if (mas2[line[k]][column[j]] < minel2 && k != i)
								minel2 = mas2[line[k]][column[j]];
						}
						if (mark[0] < minel1 + minel2)
						{
							mark[0] = minel1 + minel2;
							mark[1] = line[i]; mark[2] = column[j];
						}
					}
			from.push_back((int)mark[1]);
			to.push_back((int)mark[2]);
			mas2[(int)mark[2]][(int)mark[1]] = max;
			for(i = 0; i < iter; i++)
				if (column[i] == (int)mark[2])
				{
					column.erase(column.begin() + i);
					break;
				}
			for(i = 0; i < iter; i++)
				if (line[i] == (int)mark[1])
				{
					line.erase(line.begin() + i);
					break;
				}
		}
		from.push_back(line[0]);
		to.push_back(column[0]);
		points.push_back(Object(x, y));
		k = 0;
		while (k != -1)
			for(j = 0; j < from.size(); j++)
				if (from[j] == k)
				{
					if (to[j] != 0)
					{
						k = to[j];
						points.push_back(aims[to[j] - 1]);
					}
					else
						k = -1;
				}
		points.push_back(Object(x, y));
		for(i = 0; i <= aimssize; i++)
		{
			delete []mas[i]; delete []mas2[i];
		}
		delete []mas; delete []mas2;
		delete []g; delete []h;
	}
};
void UAV::elaborateRoat(vector<GeoObject> objects)
{
	cout << '\n' << "___UAV___"  << '\n';
	vector<Object> roating(points);
	//for (int i = 0; i < objects.size(); i++)
	//	cout << objects[i].getX() << "; " << objects[i].getY() << "     ";
	//cout << '\n' << "_____"  << '\n' << "points:  ";
	//for (int i = 0; i < points.size(); i++)
	//	cout << points[i].getX() << "; " << points[i].getY() << "     ";
	//cout << '\n' << "_____"  << '\n';
	vector<GeoObject> onway;
	points.clear();
	for (int i = 0; i < roating.size() - 1; i++)
	{
		points.push_back(roating[i]);
		for (int j = 0; j < objects.size(); j++)
			if (objects[j].onWay(points.back().getX(), points.back().getY(), roating[i + 1].getX(), roating[i + 1].getY()))
				onway.push_back(objects[j]);
		sort(onway.begin(), onway.end(), points.back());
		for (int j = 0; j < onway.size(); j++)
			if (onway[j].onWay(points.back().getX(), points.back().getY(), roating[i + 1].getX(), roating[i + 1].getY()))
				points.push_back(onway[j].point(points.back().getX(), points.back().getY(), roating[i + 1].getX(), roating[i + 1].getY()));
		onway.clear();
	}
	points.push_back(roating.back());
	//cout << '\n' << "_____"  << '\n' << "points1:  ";
	for (int i = 0; i < points.size(); i++)
		cout << points[i].getX() << "; " << points[i].getY() << "    ";
};
vector<Object> UAV::getRoat()
{
	return points;
};
