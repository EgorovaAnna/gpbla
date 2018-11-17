#include "addmap.h"
#include "ui_addmap.h"

AddMap::AddMap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMap)
{
    ui -> setupUi(this);
    ui -> label_3 -> hide();
    ui -> toolButton_2 -> hide();
    ui -> pathLine_2 -> hide();
    warning = new WarningAdding(this);
    connect(warning, &WarningAdding::ok, this, &AddMap::warningClose);
}

AddMap::~AddMap()
{
    delete ui;
}

void AddMap::on_pushButton_clicked()
{
    path = ui -> pathLine -> text();
    latlon[0][0] = ui -> lat00 -> text();
    latlon[1][0] = ui -> lon00 -> text();
    latlon[0][1] = ui -> lat10 -> text();
    latlon[1][1] = ui -> lon10 -> text();
    latlon[0][2] = ui -> lat01 -> text();
    latlon[1][2] = ui -> lon01 -> text();
    latlon[0][3] = ui -> lat11 -> text();
    latlon[1][3] = ui -> lon11 -> text();
    if (!path.isEmpty() && !latlon[0][0].isEmpty() && !latlon[1][0].isEmpty() && !latlon[0][3].isEmpty() && !latlon[1][3].isEmpty())
    {
        this -> close();
        emit add();
    }
    else
    {
        /*path = "/home/anna/prog/gpbla/map/map.ppm";
        latlon[0][0] = "-3";
        latlon[1][0] = "45";
        latlon[0][3] = "2.5";
        latlon[1][3] = "48";
        this -> close();
        emit add();*/ //отладочное
        this -> close();
        warning -> show();
    }
}

void AddMap::on_pushButton_2_clicked()
{
    this -> close();
    emit cancelAdding();
}

void AddMap::warningClose()
{
    this -> show();
}

void AddMap::on_toolButton_clicked()
{
    path = QFileDialog::getOpenFileName(this, tr("Open map"), "/home/", tr("Image Files (*.png *.jpg *.bmp *.ppm *pnm *tif)"));
    ui -> pathLine ->setText(path);
}
