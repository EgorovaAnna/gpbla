#ifndef ADDOBJECT_H
#define ADDOBJECT_H

#include <QDialog>
#include "warningadding.h"

namespace Ui {
class AddObject;
}

class AddObject : public QDialog
{
    Q_OBJECT

public:
    explicit AddObject(QWidget *parent = 0);
    ~AddObject();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

public:
    QString coord[2];
    QString rad;

signals:
    void add();
    void cancelAdding();

private:
    Ui::AddObject *ui;
    WarningAdding *warning;

private:
    void warningClose();
};

#endif // ADDOBJECT_H
