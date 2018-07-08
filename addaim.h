#ifndef ADDAIM_H
#define ADDAIM_H

#include <QDialog>
#include "warningadding.h"

namespace Ui {
class AddAim;
}

class AddAim : public QDialog
{
    Q_OBJECT

public:
    explicit AddAim(QWidget *parent = 0);
    ~AddAim();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

public:
    QString coord[3];

signals:
    void add();
    void cancelAdding();

private:
    Ui::AddAim *ui;
    WarningAdding *warning;

private:
    void warningClose();
};

#endif // ADDAIM_H
