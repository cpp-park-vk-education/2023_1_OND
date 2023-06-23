#include "guestmainwindow.h"
#include "ui_guestmainwindow.h"
#include <QPixmap>
#include <QIcon>

GuestMainWindow::GuestMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::GuestMainWindow)
{
    ui->setupUi(this);
    QPixmap logo;
    logo.load(":/logo.png");
    ui->Logo->setPixmap(logo);

    QPixmap voicelogo;
    voicelogo.load(":/voice.png");
    ui->VoiceLogo->setPixmap(voicelogo);

    QIcon buttonIcon(":/voice_btn.png");
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


void GuestMainWindow::on_VoiceBox_activated(int index)
{
    switch(index)
    {
        case 0:
            //формирование запроса с параметром голоса Константин
            break;

        case 1:
            //формирование запроса с параметром голоса Жанна
            break;

        case 2:
            //формирование запроса с параметром голоса Петр
            break;

        case 3:
            //формирование запроса с параметром голоса Алена
            break;

        case 4:
            //формирование запроса с параметром голоса Захар
            break;

        case 5:
            //формирование запроса с параметром голоса Катерина
            break;

        case 6:
            //формирование запроса с параметром голоса Павел
            break;
    }
}

