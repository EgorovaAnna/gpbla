#include "UAV.h"


UAV::UAV(double nx, double ny, double nz, double fA, double cH)
{
	x = nx;
	y = ny;
	z = nz;
    radioview = -1;
    if (fA != 0)
        flightAltitude = fA;
    else
        flightAltitude = 3000;
    focus = 500;
    changingHeight = cH;
};
UAV::UAV(double nx, double ny, double nz)
{
    x = nx;
    y = ny;
    z = nz;
};
void UAV::addPoint(ChangeHeight point)
{
	points.push_back(point);
}; 
void UAV::addAim(Aim newAim)
{
	aims.push_back(newAim);
};
void UAV::iteration(double dt)
{
	
}; 
void UAV::setR(double rad)
{
    if (rad > 0)
        radioview = rad;
};
void UAV::setF(double f)
{
    if (f > 0)
        focus = f;
};
void UAV::setW(double w)
{
    if (w > 0)
        way = w;
};
void UAV::setH(double h)
{
    if (h > 0)
        maxH = h;
};
void UAV::setV(double v)
{
    if (v > 0)
        velocity = v;
};
void UAV::setX(double nx)
{
    x = nx;
};
void UAV::setY(double ny)
{
    y = ny;
};
double UAV::getR()
{
	return radioview;
};
double UAV::getF()
{
	return focus;
};
double UAV::getW()
{
	return way;
};
double UAV::getH()
{
	return maxH;
};
double UAV::getV()
{
	return velocity;
};
void UAV::deleteAim(Aim aim)
{
	for(auto i = aims.begin(); i < aims.end(); i++)
		if (*i == aim)
			aims.erase(i);
};
double UAV::getX()
{
	return x;
};
double UAV::getY()
{
	return y;
};
void UAV::roat(vector<Aim> aims)
{
    if (aims.empty())
        return;
	int i, j, aimssize = aims.size(), iter, k, max = (int)pow(10, 10);
    if (aimssize == 0)
        return;
    points.clear();
	if (aimssize == 1 || aimssize == 2)
	{
        points.push_back(ChangeHeight(x, y, z));
        points.push_back(ChangeHeight(aims[0]));
        cout << aims[0].getH() << " " << points[1].getH()<< "\n ";
		if (aimssize == 2)
            points.push_back(ChangeHeight(aims[1]));
        points.push_back(ChangeHeight(x, y, z));
	}
	else
	{
        double **mas = new double*[aimssize + 1], **mas2 = new double*[aimssize + 1]; // матрица растояний
        double *g = new double[aimssize + 1], *h = new double[aimssize + 1];
        double min1, min2, mark[3], minel1, minel2;
		vector<int> column, line;
		vector<int> from, to;
		for(i = 0; i <= aimssize; i++)
		{
            mas[i] = new double[aimssize + 1];
            mas2[i] = new double[aimssize + 1];
			column.push_back(i); line.push_back(i);
		}
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
        points.push_back(ChangeHeight(x, y, z));
		k = 0;
		while (k != -1)
			for(j = 0; j < from.size(); j++)
				if (from[j] == k)
				{
					if (to[j] != 0)
					{
						k = to[j];
                        points.push_back(ChangeHeight(aims[to[j] - 1]));
					}
					else
						k = -1;
				}
        points.push_back(ChangeHeight(x, y, z));
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
    if (points.empty())
        return;
    ChangeHeight go;
    for(int i = 1; i < points.size() - 1; i++)
        points[i].setH(points[i].getH() + focus);
    cout << points[1].getH() << "     \n";
    vector<ChangeHeight> roating(points);
    int count = 0;
    if (!objects.empty())
    {
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
                {
                    go = onway[j].point(points.back().getX(), points.back().getY(), roating[i + 1].getX(), roating[i + 1].getY());
                    go.setH(flightAltitude);
                    points.push_back(go);
                }
            onway.clear();
        }
        points.push_back(roating.back());
    }
    roating = points;
    if (points.size() == 3)
    {
        if (points[1].getH() + focus != flightAltitude)
        {
            double r = (flightAltitude - (points[1].getH()))/tan(changingHeight*3.14/180) + (flightAltitude - (points[0].getH()))/tan(changingHeight*3.14/180);
            if (points[0].distance(points[1]) >= r)
            {
                r = (fabs(flightAltitude - (points[0].getH()))/tan(changingHeight*3.14/180));
                go.setX(points[0].getX() + (points[1].getX() - points[0].getX())*r/points[0].distance(points[1]));
                go.setY(points[0].getY() + (points[1].getY() - points[0].getY())*r/points[0].distance(points[1]));
                go.setH(flightAltitude);
                cout << go.getX() << " " << go.getY() << " " << r << "     \n";
                points.emplace(points.begin() + 1, go);
                count++;
                points.emplace(points.end() - 1, go);
                r = (fabs(flightAltitude - (points[1 + count].getH()))/tan(changingHeight*3.14/180));
                go.setX(points[1 + count].getX() - (points[1 + count].getX() - points[0].getX())*r/points[0].distance(points[1 + count]));
                go.setY(points[1 + count].getY() - (points[1 + count].getY() - points[0].getY())*r/points[0].distance(points[1 + count]));
                go.setH(flightAltitude);
                cout << go.getX() << " " << go.getY() <<" " << r << " " << (points[1 + count].getH()) << " " << tan(changingHeight*3.14/180)<< "      \n";
                points.emplace(points.begin() + 2, go);
                points.emplace(points.end() - 2, go);
            }
        }
        return;
    }
    for (int i = 0; i < points.size(); i++)
    {
        if (points[i + 1].getH() != flightAltitude)
        {
            double r = abs((flightAltitude - (points[i].getH()))/tan(changingHeight*3.14/180)) + abs((flightAltitude - (points[i + 1].getH()))/tan(changingHeight*3.14/180));
            cout << points[i].getX() << " "  << points[i].getY() << "; " << points[i + 1].getX() << " " << points[i + 1].getY() << "     "<< r << endl;
            if ((points[i + 1].distance(points[i]) > r && points[i + 1].getH() == flightAltitude))
            {
                if (points[i].getH() != flightAltitude)
                {
                    r = (fabs(flightAltitude - (points[i].getH()))/tan(changingHeight*3.14/180))/points[i].distance(points[i + 1]);
                    go.setX(points[i].getX() + (points[i + 1].getX() - points[i].getX())*r);
                    go.setY(points[i].getY() + (points[i + 1].getY() - points[i].getY())*r);
                    go.setH(flightAltitude);
                    roating.emplace(roating.begin() + i + 1 + count, go);
                    count++;
                }
                if (points[i + 1].getH() != flightAltitude)
                {
                    r = (fabs(flightAltitude - (points[i + 1].getH()))/tan(changingHeight*3.14/180))/points[i].distance(points[i + 1]);
                    go.setX(points[i + 1].getX() - (points[i + 1].getX() - points[i].getX())*r);
                    go.setY(points[i + 1].getY() - (points[i + 1].getY() - points[i].getY())*r);
                    go.setH(flightAltitude);
                    roating.emplace(roating.begin() + i + 1 + count, go);
                    count++;
                }
            }
        }
    }
    points = roating;
    double r = (flightAltitude - points[points.size() - 2].getH())/tan(changingHeight*3.14/180) + (flightAltitude - points.back().getH())/tan(changingHeight*3.14/180);
    if (points[points.size() - 2].distance(points.back()) > r)
    {
        r = fabs(flightAltitude - points[points.size() - 2].getH())/tan(changingHeight*3.14/180);
        r = r/points[points.size() - 2].distance(points.back());
        go.setX(points[points.size() - 2].getX() + (points.back().getX() - points[points.size() - 2].getX())*r);
        go.setY(points[points.size() - 2].getY() + (points.back().getY() - points[points.size() - 2].getY())*r);
        go.setH(flightAltitude);
        points.emplace(points.begin() + points.size() - 1, go);
        r = fabs(flightAltitude - points.back().getH())/tan(changingHeight*3.14/180);
        r = r/points[points.size() - 2].distance(points.back());
        go.setX(points.back().getX() - (points.back().getX() - points[points.size() - 2].getX())*r);
        go.setY(points.back().getY() - (points.back().getY() - points[points.size() - 2].getY())*r);
        go.setH(flightAltitude);
        points.emplace(points.begin() + points.size() - 1, go);
    }
};
vector<ChangeHeight> UAV::getRoat()
{
	return points;
};
void UAV::emptyRoats()
{
    points.clear();
};
void UAV::setRoat(vector<ChangeHeight> roating)
{
    emptyRoats();
    points = roating;
}
