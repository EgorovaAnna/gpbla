#include "addmap.h"
#include "ui_addmap.h"

AddMap::AddMap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMap)
{
    ui->setupUi(this);
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
    this -> close();
    emit add();
}
