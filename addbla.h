#ifndef ADDBLA_H
#define ADDBLA_H

#include <QDialog>
#include "warningadding.h"

namespace Ui {
class AddBLA;
}

class AddBLA : public QDialog
{
    Q_OBJECT

public:
    explicit AddBLA(QWidget *parent = 0);
    ~AddBLA();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void add();
    void cancelAdding();

public:
    QString coord[3];
    QString rad;
    QString focus;
    QString maxH;
    QString v;
    QString chH;
    QString fA;

private:
    Ui::AddBLA *ui;
    WarningAdding *warning;

private:
    void warningClose();
};

#endif // ADDBLA_H
