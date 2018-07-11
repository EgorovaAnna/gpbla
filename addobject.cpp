#include "addobject.h"
#include "ui_addobject.h"

AddObject::AddObject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddObject)
{
    ui->setupUi(this);
    warning = new WarningAdding(this);
    connect(warning, &WarningAdding::ok, this, &AddObject::warningClose);
    ui -> label_6 -> hide();
    ui -> label_7 -> hide();
    ui -> label_8 -> hide();
    ui -> label_9 -> hide();
    ui -> label_10 -> hide();
    ui -> label_11 -> hide();
    ui -> label_12 -> hide();
    ui -> label_13 -> hide();
    ui -> label_14 -> hide();
    ui -> lat_2 -> hide();
    ui -> lat_3 -> hide();
    ui -> lat_4 -> hide();
    ui -> lon_2 -> hide();
    ui -> lon_3 -> hide();
    ui -> lon_4 -> hide();
}

AddObject::~AddObject()
{
    delete ui;
}

void AddObject::on_pushButton_clicked()
{
    coord[0] = ui -> lat -> text();
    coord[1] = ui -> lon -> text();
    if (type == 0)
    {
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
    else
    {
        coord2[0] = ui -> lat_2 -> text();
        coord2[1] = ui -> lon_2 -> text();
        coord2[2] = ui -> lat_3 -> text();
        coord2[3] = ui -> lon_3 -> text();
        coord2[4] = ui -> lat_4 -> text();
        coord2[5] = ui -> lon_4 -> text();
        if (!coord[0].isEmpty() && !coord[1].isEmpty() && !coord2[0].isEmpty() && !coord2[1].isEmpty() && !coord2[2].isEmpty() && !coord2[3].isEmpty() && !coord2[4].isEmpty() && !coord2[5].isEmpty())
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

void AddObject::on_type_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "Круглое")
    {
        type = 0;
        ui -> label_rad -> show();
        ui -> r -> show();
        ui -> label_2 -> setText("Координаты центра");
        ui -> label_6 -> hide();
        ui -> label_7 -> hide();
        ui -> label_8 -> hide();
        ui -> label_9 -> hide();
        ui -> label_10 -> hide();
        ui -> label_11 -> hide();
        ui -> label_12 -> hide();
        ui -> label_13 -> hide();
        ui -> label_14 -> hide();
        ui -> lat_2 -> hide();
        ui -> lat_3 -> hide();
        ui -> lat_4 -> hide();
        ui -> lon_2 -> hide();
        ui -> lon_3 -> hide();
        ui -> lon_4 -> hide();
    }
    else
    {
        type = 1;
        ui -> label_rad -> hide();
        ui -> r -> hide();
        ui -> label_2 -> setText("Координаты угла 1");
        ui -> label_6 -> show();
        ui -> label_7 -> show();
        ui -> label_8 -> show();
        ui -> label_9 -> show();
        ui -> label_10 -> show();
        ui -> label_11 -> show();
        ui -> label_12 -> show();
        ui -> label_13 -> show();
        ui -> label_14 -> show();
        ui -> lat_2 -> show();
        ui -> lat_3 -> show();
        ui -> lat_4 -> show();
        ui -> lon_2 -> show();
        ui -> lon_3 -> show();
        ui -> lon_4 -> show();
    }
}
