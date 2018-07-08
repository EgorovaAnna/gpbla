#ifndef WARNINGADDING_H
#define WARNINGADDING_H

#include <QDialog>

namespace Ui {
class WarningAdding;
}

class WarningAdding : public QDialog
{
    Q_OBJECT

public:
    explicit WarningAdding(QWidget *parent = 0);
    ~WarningAdding();

private slots:
    void on_pushButton_clicked();

signals:
    void ok();

private:
    Ui::WarningAdding *ui;
};

#endif // WARNINGADDING_H
