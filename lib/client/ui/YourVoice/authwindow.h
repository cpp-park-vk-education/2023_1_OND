#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QDialog>
#include "regwindow.h"

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr);
    ~AuthWindow();

signals:
    void mainwindow();

private slots:
    void on_CancelBtn_clicked();

    void on_RegBtn_clicked();

    void on_LogInBtn2_clicked();

private:
    Ui::AuthWindow *ui;
    //RegWindow *regwindow;
};

#endif // AUTHWINDOW_H
