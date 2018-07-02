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
    addmap = new AddMap(this);
    addbla = new AddBLA(this);
    addaim = new AddAim(this);
    addobj = new AddObject(this);
    connect(addmap, &AddMap::add, this, &MainWindow::addMap);
    connect(addbla, &AddBLA::add, this, &MainWindow::addBLA);
    connect(addaim, &AddAim::add, this, &MainWindow::addAim);
    connect(addobj, &AddObject::add, this, &MainWindow::addObj);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addMap()
{
    mapImage.load(addmap -> path);
    //map.load("/home/anna/prog/gpbla/map/map.ppm");
    //ui ->pushButton_2-> setText( addmap -> path);
    //scene = new QGraphicsScene(this);
    //scene -> addPixmap(map);
    //scene -> setSceneRect(map.rect());
    //ui -> mapImage -> setScene(scene);
    //ui -> mapImage -> show();
    ui -> label -> setPixmap(QPixmap::fromImage(mapImage.scaledToWidth(ui -> label -> width())));
    ui -> label -> show();
    ui -> pushButton -> setEnabled(true);
    ui -> pushButton_2 -> setEnabled(true);
    ui -> pushButton_3 -> setEnabled(true);
    map = new Map(addmap -> latlon[0][0].toFloat(), addmap -> latlon[1][0].toFloat(), addmap -> latlon[0][3].toFloat(), addmap -> latlon[1][3].toFloat());
    mapim = new MapImage(*map);
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
    for (int i = max (0, (int)aimOnImage.getX() - mapImage.height()/50); i < min(mapImage.width(), (int)aimOnImage.getX() + mapImage.height()/50); i++)
        for (int j = max (0, (int)aimOnImage.getY() - mapImage.height()/50); j < min(mapImage.height(), (int)aimOnImage.getY() + mapImage.height()/50); j++)
            mapImage.setPixelColor(i, j, QColor("black"));
    ui -> label -> setPixmap(QPixmap::fromImage(mapImage.scaledToWidth(ui -> label -> width())));
    //QPainter painter(ui -> label)
    if (!(map -> getUAV()).empty())
    {
        ui -> pushButton_5 -> setEnabled(true);
        ui -> pushButton_6 -> setEnabled(true);
    }
    this -> show();
}

void MainWindow::addObj()
{
    //добавление препятствия
    GeoObject obj(addobj -> coord[0].toFloat(), addobj -> coord[1].toFloat(), addobj -> rad.toFloat());
    map -> addObject(obj);
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
    map -> divideTer();
    vector<UAV> uav = map -> getUAV();
    for (int i = 0; i < uav.size(); i++)
        mapim -> paintLine(uav[i].getRoat(), mapImage, QColor("red"));
    ui -> label -> setPixmap(QPixmap::fromImage(mapImage.scaledToWidth(ui -> label -> width())));

}

void MainWindow::on_pushButton_6_clicked()
{
    //моделирование полета
}
