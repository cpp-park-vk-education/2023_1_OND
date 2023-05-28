#include "regwindow.h"
#include "ui_regwindow.h"

RegWindow::RegWindow(QWidget *parent) : QDialog(parent), ui(new Ui::RegWindow)
{
    ui->setupUi(this);
    QPixmap logo3;
    logo3.load("/Users/muslimitsuhide/2023_1_OND/lib/client/ui/YourVoice/img/logo.png"); //need to fix the reference to relative
    ui->Logo3->setPixmap(logo3);
}

RegWindow::~RegWindow()
{
    delete ui;
}

void RegWindow::on_CancelBtn_clicked()
{

}

