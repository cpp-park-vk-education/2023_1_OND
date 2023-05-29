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

