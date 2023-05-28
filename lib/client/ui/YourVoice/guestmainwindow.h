#ifndef GUESTMAINWINDOW_H
#define GUESTMAINWINDOW_H

#include <QMainWindow>
#include "authwindow.h"
#include "devwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GuestMainWindow; }
QT_END_NAMESPACE

class GuestMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    GuestMainWindow(QWidget *parent = nullptr);
    ~GuestMainWindow();

private slots:
    void on_LogInButton_clicked();

    void on_pushButton_3_clicked();

    void on_RecordBtn_clicked();

private:
    Ui::GuestMainWindow *ui;
    AuthWindow *authwindow;
    DevWindow *devwindow;
    bool isRecording;
};
#endif // GUESTMAINWINDOW_H
