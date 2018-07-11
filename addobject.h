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

    void on_type_currentIndexChanged(const QString &arg1);

public:
    int type = 0;
    QString coord[2], coord2[6];
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
