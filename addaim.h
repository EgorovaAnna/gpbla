#ifndef ADDAIM_H
#define ADDAIM_H

#include <QDialog>

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

public:
    QString coord[3];

signals:
    void add();

private:
    Ui::AddAim *ui;
};

#endif // ADDAIM_H
