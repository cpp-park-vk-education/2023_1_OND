#ifndef GUESTMAINWINDOW_H
#define GUESTMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class GuestMainWindow; }
QT_END_NAMESPACE

class GuestMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    GuestMainWindow(QWidget *parent = nullptr);
    ~GuestMainWindow();

private:
    Ui::GuestMainWindow *ui;
};
#endif // GUESTMAINWINDOW_H
