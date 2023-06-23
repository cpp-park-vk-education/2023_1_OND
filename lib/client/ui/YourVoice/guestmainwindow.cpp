#include "guestmainwindow.h"
#include "./ui_guestmainwindow.h"
#include <QPixmap>
#include <QIcon>

GuestMainWindow::GuestMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::GuestMainWindow)
{
    ui->setupUi(this);
    QPixmap logo;
    logo.load("/Users/muslimitsuhide/2023_1_OND/lib/client/ui/YourVoice/img/logo.png"); //need to fix the reference to relative
    ui->LogoLabel->setPixmap(logo);

    QPixmap voice_img;
    voice_img.load("/Users/muslimitsuhide/2023_1_OND/lib/client/ui/YourVoice/img/voice.png"); //need to fix the reference to relative
    ui->VoiceLabel->setPixmap(voice_img);

    QIcon buttonIcon("/Users/muslimitsuhide/2023_1_OND/lib/client/ui/YourVoice/img/voice_btn.png"); //need to fix the reference to relative
    ui->RecordButton->setIcon(buttonIcon);
    ui->RecordButton->setIconSize(QSize(90, 90));
}

GuestMainWindow::~GuestMainWindow()
{
    delete ui;
}

void GuestMainWindow::on_RecordButton_clicked()
{
    if (!isRecording) {
        //startRecord();
        isRecording = true;
    } else {
        //stopRecord();
        isRecording = false;
    }
}

