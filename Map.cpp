#include "Map.h"
#define pi 3.14159265359

Map::Map()
{

};

Map::Map(double nx1, double nx2, double ny1, double ny2)
{
	if (nx1 > nx2)
	{
		x2 = nx1; 
		x1 = nx2;
	}
	else
	{
		x1 = nx1; 
		x2 = nx2;
	}
	if (ny1 > ny2)
	{
		y2 = ny1; 
		y1 = ny2;
	}
	else
	{
		y1 = ny1; 
		y2 = ny2;
	}
    restruct();
};
void Map::restruct()
{
    x1d = x1, x2d = x2, y1d = y1, y2d = y2;
    x1 = 0; y1 = 0;
    x2 = Object(x1d, y1d).distanceDegree(Object(x2d, y1d));
    y2 = Object(x1d, y1d).distanceDegree(Object(x1d, y2d));
}
template<typename T> T Map::getDegree(T object)
{
    return T(x1d + object.getX()*(x2d - x1d)/x2, y1d + object.getY()*(y2d - y1d)/y2, object.getH());
}
void Map::addObject(GeoObject newGO)
{
	int a = 0;
    sortXY();
    if (newGO.getX() <= x2d && newGO.getX() >= x1d && newGO.getY() >= y1d && newGO.getY() <= y2d)
    {
        newGO.setX((newGO.getX() - x1d)*x2/(x2d - x1d));
        newGO.setY((newGO.getY() - y1d)*y2/(y2d - y1d));
		for (int i = 0; i < objects.size(); i++)
			if (objects[i] == newGO)
				a = 1;
		if (a == 0)
			objects.push_back(newGO);
    }
		
}; 
void Map::addAim(Aim newAim)
{
	int a = 0;
    sortXY();
    if (newAim.getX() <= x2d && newAim.getX() >= x1d && newAim.getY() >= y1d && newAim.getY() <= y2d)
    {
        newAim.setX((newAim.getX() - x1d)*x2/(x2d - x1d));
        newAim.setY((newAim.getY() - y1d)*y2/(y2d - y1d));
        for (int i = 0; i < aims.size(); i++)
			if (aims[i] == newAim)
				a = 1;
		if (a == 0)
			aims.push_back(newAim);
    }
};
void Map::addUAV(UAV newUAV)
{
    newUAV.setX((newUAV.getX() - x1d)*x2/(x2d - x1d));
    newUAV.setY((newUAV.getY() - y1d)*y2/(y2d - y1d));
    uavs.push_back(newUAV);
};
void Map::readGIS(string file)
{
};
double& Map::operator[](int a)
{
	if (a == 0)
		return x1;
	if (a == 1)
		return x2;
    if (a == 2)
		return y1;
    if (a == 3)
		return y2;
    if (a == 4)
        return x1d;
    if (a == 5)
        return x2d;
    if (a == 6)
        return y1d;
    else
        return y2d;
};
void Map::sortXY()
{
    double nx1 = x1, nx2 = x2, ny1 = y1, ny2 = y2;
    if (nx1 > nx2)
    {
        x2 = nx1;
        x1 = nx2;
    }
    else
    {
        x1 = nx1;
        x2 = nx2;
    }
    if (ny1 > ny2)
    {
        y2 = ny1;
        y1 = ny2;
    }
    else
    {
        y1 = ny1;
        y2 = ny2;
    }
};

void Map::sortAims(Object centre)
{
    vector<Aim> sortedAims;
    Aim buf(aims[0].getX(), aims[0].getY(), aims[0].getH());
    for (int i = 0; i < aims.size(); i++)
    {
        if (aims[i].getY() >= centre.getY())
            sortedAims.insert(sortedAims.begin(), aims[i]);
        else
            sortedAims.push_back(aims[i]);
    }
    for (int i = 0; i < sortedAims.size(); i++)
    {
        for (int j = i + 1; j < sortedAims.size(); j++)
        {
            if (sortedAims[i].getY() >= centre.getY() && sortedAims[j].getY() >= centre.getY() && sortedAims[j].getX() >= sortedAims[i].getX())
            {
                buf = sortedAims[i];
                sortedAims[i] = sortedAims[j];
                sortedAims[j] = buf;
            }
            if (sortedAims[i].getY() < centre.getY() && sortedAims[j].getX() <= sortedAims[i].getX())
            {
                buf = sortedAims[i];
                sortedAims[i] = sortedAims[j];
                sortedAims[j] = buf;
            }
        }
    }
    aims = sortedAims;
};
void Map::sortAims(Object centre, vector<double> rad)
{
    int sorted;
    double round[2];
    vector<Aim> sortedAims;
    Aim buf(aims[0].getX(), aims[0].getY(), aims[0].getH());
    for (int i = 0; i < aims.size(); i++)
    {
        if (aims[i].getX() >= centre.getX())
            sortedAims.insert(sortedAims.begin(), aims[i]);
        else
            sortedAims.push_back(aims[i]);
    }
    for (int i = 0; i < sortedAims.size(); i++)
    {
        for (int j = i + 1; j < sortedAims.size(); j++)
        {
            if (sortedAims[i].getX() >= centre.getX() && sortedAims[j].getX() >= centre.getX() && tangensGreater(sortedAims[i], sortedAims[j], centre))
            {
                buf = sortedAims[i];
                sortedAims[i] = sortedAims[j];
                sortedAims[j] = buf;
            }
            if (sortedAims[i].getX() < centre.getX() && tangensGreater(sortedAims[i], sortedAims[j], centre))
            {
                buf = sortedAims[i];
                sortedAims[i] = sortedAims[j];
                sortedAims[j] = buf;
            }
        }
    }
    sorted = 0;
    round[0] = 0; round[1] = rad[0];
    aims = sortedAims;
    for (int i = 0; i < rad.size(); i++)
    {
        for (int j = sorted; j < aims.size(); j++)
        {
            if (centre.distance(aims[j]) >= round[0] && centre.distance(aims[j]) < round[1])
            {
                sortedAims[sorted] = aims[j];
                sorted++;
            }
        }
        round[0] = round[1]; round[1] = rad[i + 1];
    }
    aims = sortedAims;
}
bool Map::tangensGreater(Aim a, Aim b, Object centre)
{
    if (a.getX() == centre.getX())
        return b.getX() < centre.getX();
    if (b.getX() == centre.getX())
        return a.getX() > centre.getX();
    return (a.getY() - centre.getY())/(a.getX() - centre.getX()) >= (b.getY() - centre.getY())/(b.getX() - centre.getX());
}
/*void Map::sortObjects(Object centre, vector<double> rad)
{
    int sorted;
    double round[2];
    vector<Aim> sortedAims;
    Aim buf(aims[0].getX(), aims[0].getY(), aims[0].getH());
    for (int i = 0; i < aims.size(); i++)
    {
        if (aims[i].getY() >= centre.getY())
            sortedAims.insert(sortedAims.begin(), aims[i]);
        else
            sortedAims.push_back(aims[i]);
    }
    for (int i = 0; i < sortedAims.size(); i++)
    {
        for (int j = i + 1; j < sortedAims.size(); j++)
        {
            if (sortedAims[i].getY() >= centre.getY() && sortedAims[j].getY() >= centre.getY() && sortedAims[j].getX() >= sortedAims[i].getX())
            {
                buf = sortedAims[i];
                sortedAims[i] = sortedAims[j];
                sortedAims[j] = buf;
            }
            if (sortedAims[i].getY() < centre.getY() && sortedAims[j].getX() <= sortedAims[i].getX())
            {
                buf = sortedAims[i];
                sortedAims[i] = sortedAims[j];
                sortedAims[j] = buf;
            }
        }
    }
    sorted = 0;
    round[0] = 0; round[1] = rad[0];
    aims = sortedAims;
    for (int i = 0; i < rad.size(); i++)
    {
        for (int j = sorted; j < aims.size(); j++)
        {
            if (centre.distance(aims[j]) >= round[0] && centre.distance(aims[j]) < round[1])
            {
                sortedAims[sorted] = aims[j];
                sorted++;
            }
        }
        round[0] = round[1]; round[1] = rad[i + 1];
    }
    aims = sortedAims;
}*/
vector<double> Map::sortUAV()
{
    vector<double> rad;
    vector<UAV> sortedUAV = uavs;
    UAV buf;
    for (int i = 0; i < sortedUAV.size(); i++)
        if (sortedUAV[i].getR() == -1)
            sortedUAV[i].setR(x2 - x1);
    for (int i = 0; i < sortedUAV.size() - 1; i++)
    {
        for (int j = i + 1; j < sortedUAV.size(); j++)
        {
            if (sortedUAV[i].getR() > sortedUAV[j].getR())
            {
                buf = sortedUAV[i];
                sortedUAV[i] = sortedUAV[j];
                sortedUAV[j] = buf;
            }
        }
    }
    for (int i = 0; i < sortedUAV.size(); i++)
        if (rad.empty() || rad.back() != sortedUAV[i].getR())
            rad.push_back(sortedUAV[i].getR());
    for (auto i : rad)
        cout << i << "   ";
    cout << "\n";
    uavs = sortedUAV;
    return rad;
}

void Map::divideTer()
{
    vector<double> rads = sortUAV();
    vector<vector<UAV*>> uavInRad;
    vector<vector<Aim>> aimsInRad;
    vector<Aim> ai, slot;
	int aimsOnUAV = aims.size()/uavs.size(), aimssize = aims.size(), uavssize = uavs.size();
	Object centre((x2 + x1)/2, (y2 + y1)/2);
    double xx = 0, yy = 0;
    int countUAV = 0, countAim = 0, slotCount;
	if (allUVAtogether())
	{
		centre.setX(uavs[0].getX());
		centre.setY(uavs[0].getY());
	}
	else
	{
		k.clear();
		for(int i = 0; i < uavssize; i++)
		{
			xx += uavs[i].getX();
			yy += uavs[i].getY();
		}
		xx = xx/uavssize;
		yy = yy/uavssize;
		centre.setX(xx);
		centre.setY(yy);
	}
    sortAims(centre, rads);
    slotCount = aimssize%uavssize;
    uavInRad.resize(rads.size());
    aimsInRad.resize(rads.size());
	for (int i = 0; i < rads.size(); i++)
    {
        for (int j = countUAV; j < uavs.size(); j++)
        {
            if (rads[i] >= uavs[j].getR())
            {
                uavInRad[i].push_back(&(uavs[j]));
                countUAV++;
            }
            else
                break;
        }
        for (int j = countAim; j < aims.size(); j++)
        {
            if (rads[i] > aims[j].distance(centre))
            {
                aimsInRad[i].push_back(aims[j]);
                countAim++;
            }
            else
                break;
        }
    }
    countUAV = 0; countAim = 0;
    for (int i = 0; i < rads.size() - 1; i++)
    {
        if (!slot.empty())
            for (auto k : slot)
                aimsInRad[i].push_back(k);
        slot.clear();
        if (aimsInRad[i].size()/uavInRad[i].size() <= aimsOnUAV + slotCount)
        {
            for (int j = 0; j < uavInRad[i].size(); j++)
            {
                int aiSize = countAim + aimsInRad[i].size()/uavInRad[i].size();
                for (int k = countAim; k < min(aiSize, (int)aimsInRad[i].size()); k++)
                {
                    ai.push_back(aimsInRad[i][k]);
                    countAim++;
                }
                if (j < aimsInRad[i].size()%uavInRad[i].size() && countAim < aimsInRad[i].size())
                {
                    ai.push_back(aimsInRad[i][countAim]);
                    countAim++;
                }
                uavInRad[i][j] -> roat(ai);
                uavInRad[i][j] -> elaborateRoat(objects);
                countUAV++;
                ai.clear();
            }      
            countAim = 0;
        }
        else
        {
            for (int j = 0; j < uavInRad[i].size(); j++)
            {
                for (int k = countAim; k < countAim + aimsOnUAV; k++)
                {
                    ai.push_back(aimsInRad[i][k]);
                    countAim++;
                }
                if (slotCount > 0)
                {
                    ai.push_back(aimsInRad[i][countAim]);
                    slotCount--;
                    countAim++;
                }
                uavInRad[i][j] -> roat(ai);
                uavInRad[i][j] -> elaborateRoat(objects);
                countUAV++;
                ai.clear();
            }
            for (int j = countAim; j < aimsInRad[i].size(); j++)
                slot.push_back(aimsInRad[i][j]);
            countAim = 0;
        }
    }
    if (!slot.empty())
        for (auto k : slot)
            aimsInRad.back().push_back(k);
    for (int j = 0; j < uavInRad.back().size(); j++)
    {
        int aiSize = countAim + aimsInRad.back().size()/uavInRad.back().size();
        for (int k = countAim; k < min(aiSize, (int)aimsInRad.back().size()); k++)
        {
            ai.push_back(aimsInRad.back()[k]);
            countAim++;
        }
        if (j < aimsInRad.back().size()%uavInRad.back().size() && countAim < aimsInRad.back().size())
        {
            ai.push_back(aimsInRad.back()[countAim]);
            countAim++;
        }
        if (j == uavInRad.back().size() - 1 && countAim < aimsInRad.back().size())
            for (int k = countAim; k < aimsInRad.back().size(); k++)
                ai.push_back(aimsInRad.back()[k]);
        uavInRad.back()[j] -> roat(ai);
        uavInRad.back()[j] -> elaborateRoat(objects);
        countUAV++;
        ai.clear();
    }
};
void Map::resortAims(Object centre, int fromIndex, int number, vector<Aim> toInclude)
{
    int j = 0;
    for (int i = 0; i < aims.size(); i++)
        if (aims[i] == toInclude[j])
        {
            j++;
            aims.erase(aims.begin() + i);
            if (j == toInclude.size())
                break;
        }
    double min = x2 - x1 + y2 - y1;
    for (int i = fromIndex - j + 1; i < fromIndex + number + 1; i++)
    {
        if (aims[i].distance(toInclude.front()) < min)
        {
            min = aims[i].distance(toInclude.front());
        }
        else
        {
            aims.insert(aims.begin() + i - 1, toInclude.front());
            toInclude.erase(toInclude.begin());
            min = x2 - x1 + y2 - y1;
        }
    }
}
bool Map::allUVAtogether()
{
    double sum = 0;
	for (int i = 0; i < uavs.size() - 1; i++)
		sum += uavs[i].getX() - uavs[i + 1].getX() + uavs[i].getY() - uavs[i + 1].getY();
	if (sum < ((x1 + x2)/100 + (y1 + y2)/100)*uavs.size())
		return true;
	return false;
};
/*
int Map::calcAims(double k1, double b1, double k2, double b2, Object dir)
{
	int sum = 0;
    double x13, x23, y13, y23;
	for (int i = 0; i < aims.size(); i++)
	{
		x13 = (aims[i].getY() - aims[i].getX()*(dir.getY() - aims[i].getY())/(dir.getX() - aims[i].getX()) - b1)/(tan(k1) - (dir.getY() - aims[i].getY())/(dir.getX() - aims[i].getX()));
		x23 = (aims[i].getY() - aims[i].getX()*(dir.getY() - aims[i].getY())/(dir.getX() - aims[i].getX()) - b2)/(tan(k2) - (dir.getY() - aims[i].getY())/(dir.getX() - aims[i].getX()));
		y13 = tan(k1)*x13 + b1;
		y23 = tan(k2)*x23 + b2;
		if ((y13 <= min(aims[i].getY(), dir.getY()) || y13 >= max(aims[i].getY(), dir.getY())) && (y23 <= min(aims[i].getY(), dir.getY()) || y23 >= max(aims[i].getY(), dir.getY())) && (x13 <= min(aims[i].getX(), dir.getX()) || x13 >= max(aims[i].getX(), dir.getX())) && (x23 <= min(aims[i].getX(), dir.getX()) || x23 >= max(aims[i].getX(), dir.getX())))
			sum++;
	}
	return sum;
};
vector<Aim> Map::aimsForUAV(double k1, double b1, double k2, double b2, Object dir)
{
	vector<Aim> sum;
    double x13, x23, y13, y23;
    for (int i = 0; i < aims.size(); i++)
    {
        x13 = (aims[i].getY() - aims[i].getX()*(dir.getY() - aims[i].getY())/(dir.getX() - aims[i].getX()) - b1)/(tan(k1) - (dir.getY() - aims[i].getY())/(dir.getX() - aims[i].getX()));
        x23 = (aims[i].getY() - aims[i].getX()*(dir.getY() - aims[i].getY())/(dir.getX() - aims[i].getX()) - b2)/(tan(k2) - (dir.getY() - aims[i].getY())/(dir.getX() - aims[i].getX()));
        y13 = tan(k1)*x13 + b1;
        y23 = tan(k2)*x23 + b2;
		if ((y13 <= min(aims[i].getY(), dir.getY()) || y13 >= max(aims[i].getY(), dir.getY())) && (y23 <= min(aims[i].getY(), dir.getY()) || y23 >= max(aims[i].getY(), dir.getY())) && (x13 <= min(aims[i].getX(), dir.getX()) || x13 >= max(aims[i].getX(), dir.getX())) && (x23 <= min(aims[i].getX(), dir.getX()) || x23 >= max(aims[i].getX(), dir.getX())))
			sum.push_back(aims[i]); 
	}
	return sum;
};
vector<GeoObject> Map::goForUAV(double k1, double b1, double k2, double b2, Object dir)
{
	vector<GeoObject> sum;
    double x13, x23, y13, y23, k13, k23;
	Object centr((b2 - b1)/(tan(k1) - tan(k2)), tan(k1)*(b2 - b1)/(tan(k1) - tan(k2)) + b1);
	for (int i = 0; i < objects.size(); i++)
	{
		x13 = (objects[i].getY() - objects[i].getX()*(dir.getY() - objects[i].getY())/(dir.getX() - objects[i].getX()) - b1)/(tan(k1) - (dir.getY() - objects[i].getY())/(dir.getX() - objects[i].getX()));
		x23 = (objects[i].getY() - objects[i].getX()*(dir.getY() - objects[i].getY())/(dir.getX() - objects[i].getX()) - b2)/(tan(k2) - (dir.getY() - objects[i].getY())/(dir.getX() - objects[i].getX()));
		y13 = tan(k1)*x13 + b1;
		y23 = tan(k2)*x23 + b2;
		if (!(y13 >= min(objects[i].getY(), dir.getY()) && y13 <= max(objects[i].getY(), dir.getY())) && !(y23 >= min(objects[i].getY(), dir.getY()) && y23 <= max(objects[i].getY(), dir.getY())) && !(x13 >= min(objects[i].getX(), dir.getX()) && x13 <= max(objects[i].getX(), dir.getX())) && !(x23 >= min(objects[i].getX(), dir.getX()) && x23 <= max(objects[i].getX(), dir.getX())))

    double x13, x23, y13, y23, k, b;
	Object centr((b2 - b1)/(tan(k1) - tan(k2)), tan(k1)*(b2 - b1)/(tan(k1) - tan(k2)) + b1);
	k1 -= 5*pi/180; k2 += 5*pi/180;
	b1 = centr.getY() - centr.getX()*k1; b2 = centr.getY() - centr.getX()*k2; 
	for (int i = 0; i < objects.size(); i++)
	{
		k = (dir.getY() - objects[i].getY())/(dir.getX() - objects[i].getX());
		b = objects[i].getY() - objects[i].getX()*k;
		x13 = (b - b1)/(tan(k1) - k);
		x23 = (b - b2)/(tan(k2) - k);
		y13 = tan(k)*x13 + b;
		y23 = tan(k)*x23 + b;
		if(fabs(tan(k1)) > fabs(k))
			y13 = tan(k1)*x13 + b1;
		if(fabs(tan(k2)) > fabs(k))
			y13 = tan(k2)*x23 + b2;
		if ((y13 <= min(objects[i].getY(), dir.getY()) || y13 >= max(objects[i].getY(), dir.getY())) && (y23 <= min(objects[i].getY(), dir.getY()) || y23 >= max(objects[i].getY(), dir.getY())) && (x13 <= min(objects[i].getX(), dir.getX()) || x13 >= max(objects[i].getX(), dir.getX())) && (x23 <= min(objects[i].getX(), dir.getX()) || x23 >= max(objects[i].getX(), dir.getX())))
			sum.push_back(objects[i]);
	}
	return sum;
};*/
vector<UAV> Map::getUAV()
{
	return uavs;
};
vector<GeoObject> Map::getO()
{
	return objects;
};
vector<Aim> Map::getA()
{
	return aims;
};
vector<UAV> Map::getUAVdegree()
{
    vector<UAV> uavsd;
    vector<ChangeHeight> roatd;
    for (auto i : uavs)
    {
        uavsd.push_back(getDegree(i));
        if (!(i.getRoat()).empty())
            for (auto j : i.getRoat())
                roatd.push_back(getDegree(j));
        uavsd.back().setRoat(roatd);
        roatd.clear();
    }
    return uavsd;
};
vector<GeoObject> Map::getOdegree()
{
    vector<GeoObject> od;
    for (auto i : objects)
        od.push_back(getDegree(i));
    return od;
};
vector<Aim> Map::getAdegree()
{
    vector<Aim> ad;
    for (auto i : aims)
        ad.push_back(getDegree(i));
    return ad;
};

/*
void Map::createPBF(string filename)
{
    int size;
    if (!(size = uavs.size()))
    {
        QMessageBox::information(0, "Маршруты не сформированы!");
        return;
    }
    for (int i = 0; i < size; i++)
    {
        if(currentOperation->flightTasks.at(i)->uuid.isNull())
        {
            currentOperation->flightTasks.at(i)->uuid = QUuid::createUuid();
            OperFlightTaskDAO dao;
            dao.saveOperFlightTask(currentOperation);
        }

        currentOperation->flightTasks.at(i)->calcRouteTime();
        DMRpc::Route route;
        {
            DMRpc::Uuid* uuid = getProtoUuid(currentOperation->flightTasks.at(i)->uuid);
            route.set_allocated_id(uuid);
            route.set_name(QString::number(currentOperation->flightTasks.at(i)->number).toUtf8().data());
            DMRpc::UavIdentity* uav = new DMRpc::UavIdentity;
            uav->set_id(currentOperation->flightTasks.at(i)->avt->number);
            uav->set_type(currentOperation->flightTasks.at(i)->avt->avtType->id);
            route.set_allocated_uav(uav);

            QList<OperPPM> ppmRoute = currentOperation->flightTasks.at(i)->route;
            int rSize = ppmRoute.size();
            for (int j = 0; j < rSize; j++)
            {
                DMRpc::Route_RoutePoint* point = route.add_points();
                point->set_id(j+1);
                DMRpc::Point* p = new DMRpc::Point;
                DMRpc::GeoCoordinates* geo = new DMRpc::GeoCoordinates;
                geo->set_latitude(ppmRoute.at(j).point.y);
                geo->set_longitude(ppmRoute.at(j).point.x);
                geo->set_altitude(ppmRoute.at(j).h);
                //geo->set_epsg(); //TODO: óêàçàòü ÑÊ (ÏÇ-90)?
                p->set_allocated_geo(geo);
                point->set_timestamp(ppmRoute.at(j).time.toMSecsSinceEpoch());
                point->set_distance(round(ppmRoute.at(j).s));
                point->set_allocated_coords(p);
            }
        }
    }
    std::fstream output("/opt/route.pbf", std::ios::out | std::ios::trunc | std::ios::binary);
    if (!route.SerializeToOstream(&output))
        QMessageBox::information(this, "ÏÊ \"Ïëàíèðîâàíèå\"", "Îøèáêà çàïèñè ìàðøðóòà.");
};
*/
