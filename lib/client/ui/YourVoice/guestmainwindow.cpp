#include "guestmainwindow.h"
#include "ui_guestmainwindow.h"
#include <QPixmap>
#include <QIcon>

GuestMainWindow::GuestMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::GuestMainWindow)
{
    ui->setupUi(this);
    QPixmap logo;
    logo.load("/Users/muslimitsuhide/2023_1_OND/lib/client/ui/YourVoice/img/logo.png"); //need to fix the reference to relative
    ui->Logo->setPixmap(logo);

    QPixmap voicelogo;
    voicelogo.load("/Users/muslimitsuhide/2023_1_OND/lib/client/ui/YourVoice/img/voice.png"); //need to fix the reference to relative
    ui->VoiceLogo->setPixmap(voicelogo);

    QIcon buttonIcon("/Users/muslimitsuhide/2023_1_OND/lib/client/ui/YourVoice/img/voice_btn.png"); //need to fix the reference to relative
    ui->RecordBtn->setIcon(buttonIcon);
    ui->RecordBtn->setIconSize(QSize(120, 120));

    authwindow = new AuthWindow();
    connect(authwindow, &AuthWindow::mainwindow, this, &GuestMainWindow::show);

    devwindow = new DevWindow();
    connect(devwindow, &DevWindow::mainwindow, this, &GuestMainWindow::show);
}

GuestMainWindow::~GuestMainWindow()
{
    delete ui;
}


void GuestMainWindow::on_LogInButton_clicked()
{
    authwindow->show();
    this->close();
}


void GuestMainWindow::on_pushButton_3_clicked()
{
    devwindow->show();
    this->close();
}


void GuestMainWindow::on_RecordBtn_clicked()
{
    if (!isRecording) {
        //startRecord();
        isRecording = true;
    } else {
        //stopRecord();
        isRecording = false;
    }
}

