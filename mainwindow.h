#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGeoRoute>
#include "addmap.h"
#include "addbla.h"
#include "addaim.h"
#include "addobject.h"
#include "MapImage.h"

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

private:
    Ui::MainWindow *ui;
    AddMap *addmap;
    AddBLA *addbla;
    AddAim *addaim;
    AddObject *addobj;
    //QGraphicsScene *scene;
    //QPixmap map;
    QImage mapImage;
    Map *map;
    MapImage *mapim;
private:
    void addMap();
    void addBLA();
    void addAim();
    void addObj();
};

#endif // MAINWINDOW_H
