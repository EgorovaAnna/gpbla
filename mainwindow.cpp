#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addmap = new AddMap(this);
    connect(addmap, &AddMap::add, this, &MainWindow::addMap);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addMap()
{
    map.load(addmap -> path);
    //map.load("/home/anna/prog/gpbla/map/map.ppm");
    //ui ->pushButton_2-> setText( addmap -> path);
    //scene = new QGraphicsScene(this);
    //scene -> addPixmap(map);
    //scene -> setSceneRect(map.rect());
    //ui -> mapImage -> setScene(scene);
    //ui -> mapImage -> show();
    ui -> label -> setPixmap(QPixmap::fromImage(map));
    //ui ->pushButton_2-> setText();
    ui -> label -> show();
    //ui -> frame -> drawFrame();
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
}

void MainWindow::on_pushButton_2_clicked()
{
     //тут должно быть окно с полем ввода для координат цели
}

void MainWindow::on_pushButton_3_clicked()
{
     //тут должно быть окно с полями ввода для характеристик препятствия
}
void MainWindow::on_pushButton_5_clicked()
{
    //рассчет траекторий
}

void MainWindow::on_pushButton_6_clicked()
{
    //моделирование полета
}
