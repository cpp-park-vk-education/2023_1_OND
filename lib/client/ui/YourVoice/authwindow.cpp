#include "authwindow.h"
#include "ui_authwindow.h"
#include <QPixmap>
#include <QIcon>
#include <QMessageBox>

AuthWindow::AuthWindow(QWidget *parent) : QDialog(parent), ui(new Ui::AuthWindow)
{
    ui->setupUi(this);
    QPixmap logo2;
    logo2.load(":/logo.png");
    ui->Logo2->setPixmap(logo2);

    //regwindow = new RegWindow();
    //connect(regwindow, &RegWindow::authwindow, this, &AuthWindow::show);
}

AuthWindow::~AuthWindow()
{
    delete ui;
}

void AuthWindow::on_CancelBtn_clicked()
{
    this->close();
    emit mainwindow();
}


void AuthWindow::on_RegBtn_clicked()
{
    //regwindow->show();
    //this->close();
}


void AuthWindow::on_LogInBtn2_clicked()
{
    QString login = ui->NameLine->text();
    QString password = ui->PassLine->text();

    if (login == "Test" && password == "test") {
        QMessageBox::information(this, "Ура", "Все ок");
    } else {
        QMessageBox::warning(this, "Не ура", "Все не ок");
    }
}

