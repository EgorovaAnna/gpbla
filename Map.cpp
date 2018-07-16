#include "Map.h"
#define pi 3.14159265359

Map::Map()
{

};

Map::Map(float nx1, float nx2, float ny1, float ny2)
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
};
void Map::addObject(GeoObject newGO)
{
	int a = 0;
    sortXY();
	if (newGO.getX() <= x2 && newGO.getX() >= x1 && newGO.getY() >= y1 && newGO.getY() <= y2)
    {
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
	if (newAim.getX() <= x2 && newAim.getX() >= x1 && newAim.getY() >= y1 && newAim.getY() <= y2)
		for (int i = 0; i < aims.size(); i++)
			if (aims[i] == newAim)
				a = 1;
		if (a == 0)
			aims.push_back(newAim);
};
void Map::addUAV(UAV newUAV)
{
	uavs.push_back(newUAV);
};
void Map::readGIS(string file)
{
};
float& Map::operator[](int a)
{
	if (a == 0)
		return x1;
	if (a == 1)
		return x2;
	if (a == 2)
		return y1;
	else
		return y2;
};
void Map::sortXY()
{
    float nx1 = x1, nx2 = x2, ny1 = y1, ny2 = y2;
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
void Map::divideTer()
{
	//vector<Line> k;
	vector<Object> dirs;
	int aimsInSector = aims.size()/uavs.size(), aimssize = aims.size(), uavssize = uavs.size();
	Object centre((x2 + x1)/2, (y2 + y1)/2);
	float dk;
	float dxy = (x2 - x1 + y2 - y1)/10, xx = 0, yy = 0;
	int count, slot;
	if (allUVAtogether())
	{
		centre.setX(uavs[0].getX());
		centre.setY(uavs[0].getY());
	}
	else
	{
		k.clear();
		dirs.clear();
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
    sortAims(centre);
	slot = aimssize%uavssize;
	for (int i = 0; i < uavssize; i++)
	{
        uavs[i].emptyRoats();
		dk = i*360.0/(uavssize);
		k.push_back(Line(dk*pi/180, centre.getY() - centre.getX()*tan(dk*pi/180)));
		if (i > 0)
			dirs.push_back(Object(centre.getX() + cos(k[i - 1][0] + (k[i][0] - k[i - 1][0])/2)*dxy, centre.getY() + sin(k[i - 1][0] + (k[i][0] - k[i - 1][0])/2)*dxy)); 
	}
	for (int i = 1; i < uavssize; i++)
	{
		if (k[i][0] < k[i - 1][0])
		{
			k[i].setK(k[i - 1][0]);
			k[i].setB(k[i - 1][1]);
		}
		while (count = calcAims(k[i - 1][0], k[i - 1][1], k[i][0], k[i][1], dirs[i - 1]) < aimsInSector) // пересчитывать направление
		{
			k[i].setK(k[i][0] + pi/180);//подумать, какой будет сдвиг для луча
			k[i].setB(centre.getY() - centre.getX()*tan(k[i][0]));
			dirs[i - 1].setX(centre.getX() + cos(k[i - 1][0] + (k[i][0] - k[i - 1][0])/2)*dxy);
			dirs[i - 1].setY(centre.getY() + sin(k[i - 1][0] + (k[i][0] - k[i - 1][0])/2)*dxy); 
			if (count == aimsInSector)
			{
				k[i].setK(k[i][0] + pi/180);//подумать, какой будет сдвиг для луча
				k[i].setB(centre.getY() - centre.getX()*tan(k[i][0]));
				dirs[i - 1].setX(centre.getX() + cos(k[i - 1][0] + (k[i][0] - k[i - 1][0])/2)*dxy);
				dirs[i - 1].setY(centre.getY() + sin(k[i - 1][0] + (k[i][0] - k[i - 1][0])/2)*dxy); 
			}
		}
		while (count = calcAims(k[i - 1][0], k[i - 1][1], k[i][0], k[i][1], dirs[i - 1]) > aimsInSector + (slot > 0 ? 1 : 0))
		{
			k[i].setK(k[i][0] - pi/180);
			k[i].setB(centre.getY() - centre.getX()*tan(k[i][0]));
			dirs[i - 1].setX(centre.getX() + cos(k[i - 1][0] + (k[i][0] - k[i - 1][0])/2)*dxy);
			dirs[i - 1].setY(centre.getY() + sin(k[i - 1][0] + (k[i][0] - k[i - 1][0])/2)*dxy); 
			if (count == aimsInSector + 1)
			{
				k[i].setK(k[i][0] - pi/180);//подумать, какой будет сдвиг для луча
				k[i].setB(centre.getY() - centre.getX()*tan(k[i][0]));
				dirs[i - 1].setX(centre.getX() + cos(k[i - 1][0] + (k[i][0] - k[i - 1][0])/2)*dxy);
				dirs[i - 1].setY(centre.getY() + sin(k[i - 1][0] + (k[i][0] - k[i - 1][0])/2)*dxy); 
				slot --;
			}
		}
	}
	dirs.push_back(Object(centre.getX() + cos((2*pi + k[uavssize - 1][0])/2)*dxy, centre.getY() + sin((2*pi + k[uavssize - 1][0])/2)*dxy));
	for (int i = 0; i < uavssize - 1; i++)
	{
		if (k[i + 1][0] - k[i][0] >= pi)
		{
			Object d1(centre.getX() + cos(k[i][0] + (k[i + 1][0] - k[i][0])/4)*dxy, centre.getY() + sin(k[i][0] + (k[i + 1][0] - k[i][0])/4)*dxy), d2(centre.getX() + cos(k[i][0] + 3*(k[i + 1][0] - k[i][0])/4)*dxy, centre.getY() + sin(k[i][0] + 3*(k[i + 1][0] - k[i][0])/4)*dxy);
			vector<Aim> ai2, ai = aimsForUAV(k[i][0], k[i][1], (k[i + 1][0] + k[i][0])/2, centre.getY() - centre.getX()*tan((k[i + 1][0] + k[i][0])/2), dirs[i]);
			ai2 = aimsForUAV((k[i + 1][0] + k[i][0])/2, centre.getY() - centre.getX()*tan((k[i + 1][0] + k[i][0])/2), k[i + 1][0], k[i + 1][1], dirs[i]);
			ai.insert(ai.end(), ai2.begin(), ai2.end());
			uavs[i].roat(ai);
			vector<GeoObject> go2, go = goForUAV(k[i][0], k[i][1], (k[i + 1][0] + k[i][0])/2, centre.getY() - centre.getX()*tan((k[i + 1][0] + k[i][0])/2), dirs[i]);
			go2 = goForUAV((k[i + 1][0] + k[i][0])/2, centre.getY() - centre.getX()*tan((k[i + 1][0] + k[i][0])/2), k[i + 1][0], k[i + 1][1], dirs[i]);
			go.insert(go.end(), go2.begin(), go2.end());
			uavs[i].elaborateRoat(go);
			uavs[i].elaborateRoat(go);
			ai.clear(); ai2.clear();
			go.clear(); go2.clear();
		}
		else
		{
			uavs[i].roat(aimsForUAV(k[i][0], k[i][1], k[i + 1][0], k[i + 1][1], dirs[i]));
			uavs[i].elaborateRoat(goForUAV(k[i][0], k[i][1], k[i + 1][0], k[i + 1][1], dirs[i]));
			uavs[i].elaborateRoat(goForUAV(k[i][0], k[i][1], k[i + 1][0], k[i + 1][1], dirs[i]));
		}
	}
	if (2*pi + k[0][0] - k[uavssize - 1][0] >= pi)
	{
		Object d1(centre.getX() + cos(k[uavssize - 1][0] + (2*pi - k[uavssize - 1][0])/4)*dxy, centre.getY() + sin(k[uavssize - 1][0] + (2*pi - k[uavssize - 1][0])/4)*dxy), d2(centre.getX() + cos(k[uavssize - 1][0] + 3*(2*pi - k[uavssize - 1][0])/4)*dxy, centre.getY() + sin(k[uavssize - 1][0] + 3*(2*pi - k[uavssize - 1][0])/4)*dxy);
		vector<Aim> ai2, ai = aimsForUAV(k[uavssize - 1][0], k[uavssize - 1][1], (2*pi + k[0][0] + k[uavssize - 1][0])/2, centre.getY() - centre.getX()*tan((2*pi + k[0][0] + k[uavssize - 1][0])/2), d1);
		ai2 = aimsForUAV((2*pi + k[0][0] + k[uavssize - 1][0])/2, centre.getY() - centre.getX()*tan((2*pi + k[0][0] + k[uavssize - 1][0])/2), 2*pi + k[0][0], k[0][1], d2);
		ai.insert(ai.end(), ai2.begin(), ai2.end());
		uavs[uavssize - 1].roat(ai);
		vector<GeoObject> go2, go = goForUAV(k[uavssize - 1][0], k[uavssize - 1][1], (2*pi + k[0][0] + k[uavssize - 1][0])/2, centre.getY() - centre.getX()*tan((2*pi + k[0][0] + k[uavssize - 1][0])/2), d1);
		go2 = goForUAV((2*pi + k[0][0] + k[uavssize - 1][0])/2, centre.getY() - centre.getX()*tan((2*pi + k[0][0] + k[uavssize - 1][0])/2), 2*pi + k[0][0], k[0][1], d2);
		go.insert(go.end(), go2.begin(), go2.end());
		uavs[uavssize - 1].elaborateRoat(go);
		ai.clear(); ai2.clear();
		go.clear(); go2.clear();
	}
	else
	{
		uavs[uavssize - 1].roat(aimsForUAV(k[uavssize - 1][0], k[uavssize - 1][1], 2*pi + k[0][0], k[0][1], dirs.back()));
		uavs[uavssize - 1].elaborateRoat(goForUAV(k[uavssize - 1][0], k[uavssize - 1][1], 2*pi + k[0][0], k[0][1], dirs.back()));
	}
};
bool Map::allUVAtogether()
{
	float sum = 0;
	for (int i = 0; i < uavs.size() - 1; i++)
		sum += uavs[i].getX() - uavs[i + 1].getX() + uavs[i].getY() - uavs[i + 1].getY();
	if (sum < ((x1 + x2)/100 + (y1 + y2)/100)*uavs.size())
		return true;
	return false;
};
int Map::calcAims(float k1, float b1, float k2, float b2, Object dir)
{
	int sum = 0;
	float x13, x23, y13, y23;
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
vector<Aim> Map::aimsForUAV(float k1, float b1, float k2, float b2, Object dir)
{
	vector<Aim> sum;
    float x13, x23, y13, y23;
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
vector<GeoObject> Map::goForUAV(float k1, float b1, float k2, float b2, Object dir)
{
	vector<GeoObject> sum;
	/*float x13, x23, y13, y23, k13, k23;
	Object centr((b2 - b1)/(tan(k1) - tan(k2)), tan(k1)*(b2 - b1)/(tan(k1) - tan(k2)) + b1);
	for (int i = 0; i < objects.size(); i++)
	{
		x13 = (objects[i].getY() - objects[i].getX()*(dir.getY() - objects[i].getY())/(dir.getX() - objects[i].getX()) - b1)/(tan(k1) - (dir.getY() - objects[i].getY())/(dir.getX() - objects[i].getX()));
		x23 = (objects[i].getY() - objects[i].getX()*(dir.getY() - objects[i].getY())/(dir.getX() - objects[i].getX()) - b2)/(tan(k2) - (dir.getY() - objects[i].getY())/(dir.getX() - objects[i].getX()));
		y13 = tan(k1)*x13 + b1;
		y23 = tan(k2)*x23 + b2;
		if (!(y13 >= min(objects[i].getY(), dir.getY()) && y13 <= max(objects[i].getY(), dir.getY())) && !(y23 >= min(objects[i].getY(), dir.getY()) && y23 <= max(objects[i].getY(), dir.getY())) && !(x13 >= min(objects[i].getX(), dir.getX()) && x13 <= max(objects[i].getX(), dir.getX())) && !(x23 >= min(objects[i].getX(), dir.getX()) && x23 <= max(objects[i].getX(), dir.getX())))
		*/
	float x13, x23, y13, y23, k, b;
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
};
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
vector<Line> Map::getK()
{
	return k;
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
