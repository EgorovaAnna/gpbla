#include "addobject.h"
#include "ui_addobject.h"

AddObject::AddObject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddObject)
{
    ui->setupUi(this);
    warning = new WarningAdding(this);
    connect(warning, &WarningAdding::ok, this, &AddObject::warningClose);
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
    if (!coord[0].isEmpty() && !coord[1].isEmpty() && !rad.isEmpty())
    {
        this -> close();
        emit add();
    }
    else
    {
        this -> close();
        warning -> show();
    }
}

void AddObject::on_pushButton_2_clicked()
{
    this -> close();
    emit cancelAdding();
}

void AddObject::warningClose()
{
    this -> show();
}
