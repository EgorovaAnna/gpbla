#ifndef ADDBLA_H
#define ADDBLA_H

#include <QDialog>

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

signals:
    void add();

public:
    QString coord[3];
    QString rad;
    QString focus;
    QString maxH;
    QString v;

private:
    Ui::AddBLA *ui;
};

#endif // ADDBLA_H
