#ifndef ADDOBJECT_H
#define ADDOBJECT_H

#include <QDialog>

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

public:
    QString coord[2];
    QString rad;

signals:
    void add();

private:
    Ui::AddObject *ui;
};

#endif // ADDOBJECT_H
