#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGeoRoute>
#include "addmap.h"
#include "addbla.h"
#include "addaim.h"
#include "addobject.h"
#include "MapImage.h"
#include "saveflight.h"

#define MAX_SCALE 8

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_4_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_plusSize_clicked();
    void on_minusSize_clicked();
    void on_upMap_clicked();
    void on_downMap_clicked();
    void on_leftMap_clicked();
    void on_rightMap_clicked();

private:
    Ui::MainWindow *ui;
    AddMap *addmap;
    AddBLA *addbla;
    AddAim *addaim;
    AddObject *addobj;
    QImage mapImage, currentMap;
    Map *map;
    MapImage *mapim;
    SaveFlight *saveflight;
    int scale = 1, point[2] = {0, 0};

private:
    void addMap();
    void addBLA();
    void addAim();
    void addObj();
    void saved();
    void zoomOut();
    void deepen();

};

#endif // MAINWINDOW_H
