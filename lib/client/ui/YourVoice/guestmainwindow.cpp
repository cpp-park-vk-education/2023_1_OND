#include "guestmainwindow.h"
#include "./ui_guestmainwindow.h"
#include <QPixmap>
#include <QIcon>

GuestMainWindow::GuestMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::GuestMainWindow)
{
    ui->setupUi(this);
    QPixmap logo;
    logo.load("/Users/muslimitsuhide/2023_1_OND/lib/client/ui/YourVoice/img/logo.png"); //need to fix the reference to relative
    ui->label->setPixmap(logo);

    QPixmap voice_img;
    voice_img.load("/Users/muslimitsuhide/2023_1_OND/lib/client/ui/YourVoice/img/voice.png"); //need to fix the reference to relative
    ui->label_2->setPixmap(voice_img);

    QIcon buttonIcon("/Users/muslimitsuhide/2023_1_OND/lib/client/ui/YourVoice/img/voice_btn.png"); //need to fix the reference to relative
    ui->pushButton_2->setIcon(buttonIcon);
    ui->pushButton_2->setIconSize(QSize(90, 90));

}

GuestMainWindow::~GuestMainWindow()
{
    delete ui;
}

