#ifndef SAVEFLIGHT_H
#define SAVEFLIGHT_H

#include <QDialog>
#include <string>
#include "warningadding.h"

namespace Ui {
class SaveFlight;
}

class SaveFlight : public QDialog
{
    Q_OBJECT

public:
    explicit SaveFlight(QWidget *parent = 0);
    ~SaveFlight();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

public:
    std::string path;
    std::string name;
    bool createPBF = false;

signals:
    void saved();
    void cancelSaving();

private:
    Ui::SaveFlight *ui;
    WarningAdding *warning;

private:
    void warningClose();
};

#endif // SAVEFLIGHT_H
