#include "guestmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GuestMainWindow w;
    w.show();
    return a.exec();
}
