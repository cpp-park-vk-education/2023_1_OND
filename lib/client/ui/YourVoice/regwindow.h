#ifndef REGWINDOW_H
#define REGWINDOW_H

#include <QDialog>
#include "authwindow.h"

namespace Ui {
class RegWindow;
}

class RegWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegWindow(QWidget *parent = nullptr);
    ~RegWindow();

signals:
    void authwindow();

private slots:
    void on_CancelBtn_clicked();

private:
    Ui::RegWindow *ui;
};

#endif // REGWINDOW_H
