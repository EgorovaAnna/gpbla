#ifndef ADDMAP_H
#define ADDMAP_H

#include <QDialog>
#include "warningadding.h"

namespace Ui {
class AddMap;
}

class AddMap : public QDialog
{
    Q_OBJECT
public:
    QString path;
    QString latlon[2][4];
public:
    explicit AddMap(QWidget *parent = 0);
    ~AddMap();
signals:
    void add();
    void cancelAdding();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::AddMap *ui;
    WarningAdding *warning;

private:
    void warningClose();
};

#endif // ADDMAP_H
