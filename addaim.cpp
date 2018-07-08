#include "addaim.h"
#include "ui_addaim.h"

AddAim::AddAim(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAim)
{
    ui->setupUi(this);
    warning = new WarningAdding(this);
    connect(warning, &WarningAdding::ok, this, &AddAim::warningClose);
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
    if (!coord[0].isEmpty() && !coord[1].isEmpty() && !coord[2].isEmpty())
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

void AddAim::on_pushButton_2_clicked()
{
    this -> close();
    emit cancelAdding();
}

void AddAim::warningClose()
{
    this -> show();
}
