/********************************************************************************
** Form generated from reading UI file 'guestmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUESTMAINWINDOW_H
#define UI_GUESTMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GuestMainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QPushButton *pushButton;
    QLabel *label;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QFrame *frame_2;
    QPushButton *pushButton_2;
    QLabel *label_2;

    void setupUi(QMainWindow *GuestMainWindow)
    {
        if (GuestMainWindow->objectName().isEmpty())
            GuestMainWindow->setObjectName("GuestMainWindow");
        GuestMainWindow->resize(800, 489);
        GuestMainWindow->setMinimumSize(QSize(800, 480));
        GuestMainWindow->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:0, y2:0, stop:0 rgba(81, 0, 135, 255), stop:0.427447 rgba(41, 18, 129, 235), stop:1 rgba(155, 79, 185, 255));"));
        GuestMainWindow->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        centralwidget = new QWidget(GuestMainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setMinimumSize(QSize(0, 50));
        frame->setMaximumSize(QSize(16777215, 50));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(680, 10, 100, 32));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius:  15px;\n"
"    background-color:  rgb(116,74,246);\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(192,74,246);\n"
"    border: 1px solid rgb(116,74,246);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color:  red;\n"
"}"));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 4, 45, 41));
        label->setPixmap(QPixmap(QString::fromUtf8("img/logo.png")));
        label->setScaledContents(true);
        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(100, 10, 100, 32));
        pushButton_3->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color:  none;\n"
"    border: none;\n"
"    color: grey;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"     color: black;\n"
"}\n"
""));
        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(180, 10, 100, 32));
        pushButton_4->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color:  none;\n"
"    border: none;\n"
"    color: grey;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"     color: black;\n"
"}\n"
""));
        pushButton_5 = new QPushButton(frame);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(270, 10, 100, 32));
        pushButton_5->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color:  none;\n"
"    border: none;\n"
"    color: grey;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"     color: black;\n"
"}\n"
""));

        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setStyleSheet(QString::fromUtf8("background-color: none;"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        pushButton_2 = new QPushButton(frame_2);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(340, 190, 101, 91));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color:  none;\n"
"    border: none;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("img/voice_btn.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon);
        pushButton_2->setIconSize(QSize(90, 90));
        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 160, 801, 151));
        label_2->setPixmap(QPixmap(QString::fromUtf8("img/voice.png")));
        label_2->setScaledContents(true);
        label_2->setWordWrap(false);
        label_2->setOpenExternalLinks(false);
        label_2->raise();
        pushButton_2->raise();

        verticalLayout->addWidget(frame_2);

        GuestMainWindow->setCentralWidget(centralwidget);

        retranslateUi(GuestMainWindow);

        QMetaObject::connectSlotsByName(GuestMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GuestMainWindow)
    {
        GuestMainWindow->setWindowTitle(QCoreApplication::translate("GuestMainWindow", "YourVoice", nullptr));
        pushButton->setText(QCoreApplication::translate("GuestMainWindow", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        label->setText(QString());
        pushButton_3->setText(QCoreApplication::translate("GuestMainWindow", "btn_1", nullptr));
        pushButton_4->setText(QCoreApplication::translate("GuestMainWindow", "btn_2", nullptr));
        pushButton_5->setText(QCoreApplication::translate("GuestMainWindow", "btn_3", nullptr));
        pushButton_2->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GuestMainWindow: public Ui_GuestMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUESTMAINWINDOW_H
