#include "warningadding.h"
#include "ui_warningadding.h"

WarningAdding::WarningAdding(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarningAdding)
{
    ui->setupUi(this);
}

WarningAdding::~WarningAdding()
{
    delete ui;
}

void WarningAdding::on_pushButton_clicked()
{
    this -> close();
    emit ok();
}
