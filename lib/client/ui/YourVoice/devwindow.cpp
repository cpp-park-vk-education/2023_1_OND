#include "devwindow.h"
#include "ui_devwindow.h"
#include <QPixmap>

DevWindow::DevWindow(QWidget *parent) : QDialog(parent), ui(new Ui::DevWindow)
{
    ui->setupUi(this);
    QPixmap logo11;
    logo11.load(":/photo1.png");
    ui->label->setPixmap(logo11);

    QPixmap logo12;
    logo12.load(":/photo2.png");
    ui->label_6->setPixmap(logo12);

    QPixmap logo13;
    logo13.load(":/photo3.png");
    ui->label_9->setPixmap(logo13);

    QPixmap logo14;
    logo14.load(":/photo4.png");
    ui->label_12->setPixmap(logo14);

}

DevWindow::~DevWindow()
{
    delete ui;
}

void DevWindow::on_CancelBtn_2_clicked()
{
    this->close();
    emit mainwindow();
}

