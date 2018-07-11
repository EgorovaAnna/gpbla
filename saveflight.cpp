#include "saveflight.h"
#include "ui_saveflight.h"

SaveFlight::SaveFlight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveFlight)
{
    ui->setupUi(this);
}

SaveFlight::~SaveFlight()
{
    delete ui;
    warning = new WarningAdding(this);
    connect(warning, &WarningAdding::ok, this, &SaveFlight::warningClose);
}

void SaveFlight::on_pushButton_2_clicked()
{
    this -> close();
    emit cancelSaving();
}

void SaveFlight::on_pushButton_clicked()
{
    name = (ui -> fileName -> text()).toStdString();
    path = (ui -> pathLine -> text()).toStdString();
    if (!path.empty() && !name.empty())
    {
        this -> close();
        emit saved();
    }
    else
    {
        this -> close();
        warning -> show();
    }
}
void SaveFlight::warningClose()
{
    this -> show();
}
