#ifndef ADDMAP_H
#define ADDMAP_H

#include <QDialog>

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
private slots:
    void on_pushButton_clicked();

private:
    Ui::AddMap *ui;
};

#endif // ADDMAP_H
