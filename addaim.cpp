#include "addaim.h"
#include "ui_addaim.h"

AddAim::AddAim(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAim)
{
    ui->setupUi(this);
}

AddAim::~AddAim()
{
    delete ui;
}

void AddAim::on_pushButton_clicked()
{
    coord[0] = ui -> lat -> text();
    coord[1] = ui -> lon -> text();
    coord[2] = ui -> h -> text();
    this -> close();
    emit add();
}
