#include "addobject.h"
#include "ui_addobject.h"

AddObject::AddObject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddObject)
{
    ui->setupUi(this);
}

AddObject::~AddObject()
{
    delete ui;
}

void AddObject::on_pushButton_clicked()
{
    coord[0] = ui -> lat -> text();
    coord[1] = ui -> lon -> text();
    rad = ui -> r -> text();
    this -> close();
    emit add();
}
