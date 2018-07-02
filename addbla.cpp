#include "addbla.h"
#include "ui_addbla.h"

AddBLA::AddBLA(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBLA)
{
    ui->setupUi(this);
}

AddBLA::~AddBLA()
{
    delete ui;
}

void AddBLA::on_pushButton_clicked()
{
    coord[0] = ui -> lat -> text();
    coord[1] = ui -> lon -> text();
    coord[2] = ui -> h -> text();
    rad = ui -> rad -> text();
    focus = ui -> focus -> text();
    maxH = ui -> maxH -> text();
    v = ui -> v -> text();
    this -> close();
    emit add();
}
