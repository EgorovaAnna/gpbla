#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui -> setupUi(this);
    ui -> pushButton -> setEnabled(false);
    ui -> pushButton_2 -> setEnabled(false);
    ui -> pushButton_3 -> setEnabled(false);
    ui -> pushButton_5 -> setEnabled(false);
    ui -> pushButton_6 -> setEnabled(false);
    ui -> pushButton_7 -> setEnabled(false);
    ui -> minusSize -> setEnabled(false);
    ui -> plusSize -> setEnabled(false);
    ui -> upMap -> setEnabled(false);
    ui -> downMap -> setEnabled(false);
    ui -> leftMap -> setEnabled(false);
    ui -> rightMap -> setEnabled(false);
    addmap = new AddMap(this);
    addbla = new AddBLA(this);
    addaim = new AddAim(this);
    addobj = new AddObject(this);
    saveflight = new SaveFlight(this);
    connect(addmap, &AddMap::add, this, &MainWindow::addMap);
    connect(addbla, &AddBLA::add, this, &MainWindow::addBLA);
    connect(addaim, &AddAim::add, this, &MainWindow::addAim);
    connect(addobj, &AddObject::add, this, &MainWindow::addObj);
    connect(saveflight, &SaveFlight::saved, this, &MainWindow::saved);
    connect(addmap, &AddMap::cancelAdding, this, &MainWindow::show);
    connect(addbla, &AddBLA::cancelAdding, this, &MainWindow::show);
    connect(addaim, &AddAim::cancelAdding, this, &MainWindow::show);
    connect(addobj, &AddObject::cancelAdding, this, &MainWindow::show);
    connect(saveflight, &SaveFlight::cancelSaving, this, &MainWindow::show);
    map = new Map();
    mapim = new MapImage(*map);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saved()
{
    ofstream fout;
    vector<UAV> uav = map -> getUAV();
    vector <Object> object;
    vector<GeoObject> go = map -> getO();
    vector<Aim> aim = map -> getA();
    const string str = (saveflight -> path + "/" + saveflight -> name);
    fout.open(str);
    fout << "Заданы цели: " << "\n\t\t";
    for (int i = 0; i < aim.size(); i++)
        fout << "(" << aim[i].getX() << " ; " << aim[i].getY() << " )\n\t\t";
    fout << "\nЗаданы препятствия: " << "\n\t\t";
    for (int i = 0; i < go.size(); i++)
        fout << "(" << go[i].getX() << " ; " << go[i].getY() << " )\n\t\t";
    for (int i = 0; i < uav.size(); i++)
    {
        object = uav[i].getRoat();
        fout << "\nПоворотные точки маршрута БЛА № " << i + 1 << ":\n    Вылет из точки "; //добавить вывод характеристик?
        for (int j = 0; j < object.size() - 1; j++)
            fout << "(" << object[j].getX() << " ; " << object[j].getY() << " )\n\t\t\t";
        fout << "Возвращение в точку " << "(" << object[object.size() - 1].getX() << " ; " << object[object.size() - 1].getY() << " )\n\n";
    }
    fout.close();
}

void MainWindow::addMap()
{
    zoomOut();
    mapImage.load(addmap -> path);
    ui -> label -> setPixmap(QPixmap::fromImage(mapImage.scaledToWidth(ui -> label -> width())));
    ui -> label -> show();
    ui -> pushButton -> setEnabled(true);
    ui -> pushButton_2 -> setEnabled(true);
    ui -> pushButton_3 -> setEnabled(true);
    ui -> plusSize -> setEnabled(true);
    map -> operator [](0) = addmap -> latlon[0][0].toFloat();
    map -> operator [](1) = addmap -> latlon[1][0].toFloat();
    map -> operator [](2) = addmap -> latlon[0][3].toFloat();
    map -> operator [](3) = addmap -> latlon[1][3].toFloat();
    mapim -> setImage(mapImage.width(), mapImage.height());
    this -> show();
}

void MainWindow::addBLA()
{
    //добавление бла
    UAV uav(addbla -> coord[0].toFloat(), addbla -> coord[1].toFloat(), addbla -> coord[2].toFloat(), 0);
    uav.setR(addbla -> rad.toFloat());
    uav.setF(addbla -> focus.toFloat());
    uav.setH(addbla -> maxH.toFloat());
    uav.setV(addbla -> v.toFloat());
    map -> addUAV(uav);
    if (!(map -> getA()).empty())
    {
        ui -> pushButton_5 -> setEnabled(true);
        ui -> pushButton_6 -> setEnabled(true);
    }
    this -> show();
}

void MainWindow::addAim()
{
    //добавление цели
    Aim aim(addaim -> coord[0].toFloat(), addaim -> coord[1].toFloat(), addaim -> coord[2].toFloat());
    Object aimOnImage = mapim -> coordinateToPoint(aim.getX(), aim.getY());
    map -> addAim(aim);
    /*for (int i = max (0, (int)aimOnImage.getX() - mapImage.height()/50); i < min(mapImage.width(), (int)aimOnImage.getX() + mapImage.height()/50); i++)
        for (int j = max (0, (int)aimOnImage.getY() - mapImage.height()/50); j < min(mapImage.height(), (int)aimOnImage.getY() + mapImage.height()/50); j++)
            mapImage.setPixelColor(i, j, QColor("black"));
    ui -> label -> setPixmap(QPixmap::fromImage(mapImage.scaledToWidth(ui -> label -> width())));/home/anna/prog/gpbla/map*/
    //QPainter painter(ui -> label)
    mapim -> paintAims(map -> getA(), mapImage);
    if (!(map -> getUAV()).empty())
    {
        ui -> pushButton_5 -> setEnabled(true);
        //ui -> pushButton_6 -> setEnabled(true);
    }
    ui -> label -> setPixmap(QPixmap::fromImage(mapImage.scaledToWidth(ui -> label -> width())));
    zoomOut();
    this -> show();
}

void MainWindow::addObj()
{
    //добавление препятствия
    GeoObject obj(addobj -> coord[0].toFloat(), addobj -> coord[1].toFloat(), addobj -> rad.toFloat());
    map -> addObject(obj);
    mapim -> paintObjects(map -> getO(), mapImage);
    ui -> label -> setPixmap(QPixmap::fromImage(mapImage.scaledToWidth(ui -> label -> width())));
    zoomOut();
    this -> show();
}

void MainWindow::on_pushButton_4_clicked()
{
    //тут должно быть окно с полем ввода для карты
    this -> hide();
    addmap -> show();
}

void MainWindow::on_pushButton_clicked()
{
     //тут должно быть окно с полями ввода для характеристик БЛА
    this -> hide();
    addbla -> show();
}

void MainWindow::on_pushButton_2_clicked()
{
     //тут должно быть окно с полем ввода для координат цели
    this -> hide();
    addaim -> show();
}

void MainWindow::on_pushButton_3_clicked()
{
    this -> hide();
    addobj -> show();
     //тут должно быть окно с полями ввода для характеристик препятствия
}
void MainWindow::on_pushButton_5_clicked()
{
    //рассчет траекторий
    if ((map -> getA()).size() > 0 && (map -> getUAV()).size() > 0)
    {
        map -> divideTer();
        vector<UAV> uav = map -> getUAV();
        for (int i = 0; i < uav.size(); i++)
            mapim -> paintLine(uav[i].getRoat(), mapImage, QColor("red"));
        ui -> label -> setPixmap(QPixmap::fromImage(mapImage.scaledToWidth(ui -> label -> width())));
        zoomOut();
        saveflight -> show();
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    //моделирование полета
}

void MainWindow::on_pushButton_7_clicked()
{
    //считывание полетного задания из файла
}

void MainWindow::on_plusSize_clicked()
{
    scale = scale*2;
    currentMap = mapImage.copy(point[0], point[1], mapImage.width()/scale, mapImage.height()/scale);
    deepen();
    if (scale == MAX_SCALE)
        ui -> plusSize -> setEnabled(false);
    ui -> label -> setPixmap(QPixmap::fromImage(currentMap.scaledToWidth(ui -> label -> width())));
}

void MainWindow::on_minusSize_clicked()
{
    if (scale == MAX_SCALE)
        ui -> plusSize -> setEnabled(true);
    if (!(ui -> downMap -> isEnabled()))
        point[1] = point[1] - mapImage.height()/scale;
    if (!(ui -> rightMap -> isEnabled()))
        point[0] = point[0] - mapImage.width()/scale;
    scale = scale/2;
    if (mapImage.width() - point[0] < 2*mapImage.width()/MAX_SCALE)
        ui -> rightMap -> setEnabled(false);
    if (mapImage.height() - point[1] < 2*mapImage.height()/MAX_SCALE)
        ui -> downMap -> setEnabled(false);
    if (scale == 1)
        zoomOut();
    currentMap = mapImage.copy(point[0], point[1], mapImage.width()/scale, mapImage.height()/scale);
    ui -> label -> setPixmap(QPixmap::fromImage(currentMap.scaledToWidth(ui -> label -> width())));
}

void MainWindow::on_upMap_clicked()
{
    point[1] = max(point[1] - mapImage.height()/scale, 0);
    ui -> downMap -> setEnabled(true);
    if (point[1] == 0 || point[1] < 2*mapImage.height()/MAX_SCALE)
        ui -> upMap -> setEnabled(false);
    currentMap = mapImage.copy(point[0], point[1], mapImage.width()/scale, mapImage.height()/scale);
    ui -> label -> setPixmap(QPixmap::fromImage(currentMap.scaledToWidth(ui -> label -> width())));
}

void MainWindow::on_downMap_clicked()
{
    point[1] = min(point[1] + mapImage.height()/scale, mapImage.height() - mapImage.height()/scale);
    ui -> upMap -> setEnabled(true);
    if (point[1] == mapImage.height() - mapImage.height()/scale || mapImage.height() - point[1] < 2*mapImage.height()/MAX_SCALE)
        ui -> downMap -> setEnabled(false);
    currentMap = mapImage.copy(point[0], point[1], mapImage.width()/scale, mapImage.height()/scale);
    ui -> label -> setPixmap(QPixmap::fromImage(currentMap.scaledToWidth(ui -> label -> width())));
}

void MainWindow::on_leftMap_clicked()
{
    point[0] = max(point[0] - mapImage.width()/scale, 0);
    ui -> rightMap -> setEnabled(true);
    if (point[0] == 0 || point[0] < 2*mapImage.width()/MAX_SCALE)
        ui -> leftMap -> setEnabled(false);
    currentMap = mapImage.copy(point[0], point[1], mapImage.width()/scale, mapImage.height()/scale);
    ui -> label -> setPixmap(QPixmap::fromImage(currentMap.scaledToWidth(ui -> label -> width())));
}

void MainWindow::on_rightMap_clicked()
{
    point[0] = min(point[0] + mapImage.width()/scale, mapImage.width() - mapImage.width()/scale);
    ui -> leftMap -> setEnabled(true);
    if (point[0] == mapImage.width() - mapImage.width()/scale || mapImage.width() - point[0] < 2*mapImage.width()/MAX_SCALE)
        ui -> rightMap -> setEnabled(false);
    currentMap = mapImage.copy(point[0], point[1], mapImage.width()/scale, mapImage.height()/scale);
    ui -> label -> setPixmap(QPixmap::fromImage(currentMap.scaledToWidth(ui -> label -> width())));
}

void MainWindow::zoomOut()
{
    scale = 1;
    point[0] = 0; point[1] = 0;
    ui -> plusSize -> setEnabled(true);
    ui -> minusSize -> setEnabled(false);
    ui -> upMap -> setEnabled(false);
    ui -> downMap -> setEnabled(false);
    ui -> leftMap -> setEnabled(false);
    ui -> rightMap -> setEnabled(false);
}

void MainWindow::deepen()
{
    ui -> minusSize -> setEnabled(true);
    ui -> downMap -> setEnabled(true);
    ui -> rightMap -> setEnabled(true);
}
