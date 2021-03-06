#include "addbla.h"
#include "ui_addbla.h"

AddBLA::AddBLA(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBLA)
{
    ui->setupUi(this);
    ui -> type -> hide();
    warning = new WarningAdding(this);
    connect(warning, &WarningAdding::ok, this, &AddBLA::warningClose);
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
    chH = ui -> chH -> text();
    fA = ui -> fA -> text();
    if (!coord[0].isEmpty() && !coord[1].isEmpty() && !coord[2].isEmpty() && !fA.isEmpty() && !focus.isEmpty())
    {
        this -> close();
        emit add();
    }
    else
    {
        /*coord[0] = "0";
        coord[1] = "46";
        coord[2] = "0";
        focus ="500";
        this -> close();
        emit add();*/ //отладочное
        this -> close();
        warning -> show();
    }
}

void AddBLA::on_pushButton_2_clicked()
{
    this -> close();
    emit cancelAdding();
}

void AddBLA::warningClose()
{
    this -> show();
}
