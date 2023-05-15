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
    QPushButton *LogInButton;
    QLabel *LogoLabel;
    QPushButton *EmptyButton1;
    QPushButton *EmptyButton2;
    QPushButton *EmptyButton3;
    QFrame *frame_2;
    QPushButton *RecordButton;
    QLabel *VoiceLabel;

    void setupUi(QMainWindow *GuestMainWindow)
    {
        if (GuestMainWindow->objectName().isEmpty())
            GuestMainWindow->setObjectName("GuestMainWindow");
        GuestMainWindow->setEnabled(true);
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
        LogInButton = new QPushButton(frame);
        LogInButton->setObjectName("LogInButton");
        LogInButton->setGeometry(QRect(680, 10, 100, 32));
        LogInButton->setCursor(QCursor(Qt::PointingHandCursor));
        LogInButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        LogoLabel = new QLabel(frame);
        LogoLabel->setObjectName("LogoLabel");
        LogoLabel->setGeometry(QRect(10, 4, 45, 41));
        LogoLabel->setPixmap(QPixmap(QString::fromUtf8("img/logo.png")));
        LogoLabel->setScaledContents(true);
        EmptyButton1 = new QPushButton(frame);
        EmptyButton1->setObjectName("EmptyButton1");
        EmptyButton1->setGeometry(QRect(100, 10, 100, 32));
        EmptyButton1->setCursor(QCursor(Qt::PointingHandCursor));
        EmptyButton1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color:  none;\n"
"    border: none;\n"
"    color: grey;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"     color: black;\n"
"}\n"
""));
        EmptyButton2 = new QPushButton(frame);
        EmptyButton2->setObjectName("EmptyButton2");
        EmptyButton2->setGeometry(QRect(180, 10, 100, 32));
        EmptyButton2->setCursor(QCursor(Qt::PointingHandCursor));
        EmptyButton2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color:  none;\n"
"    border: none;\n"
"    color: grey;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"     color: black;\n"
"}\n"
""));
        EmptyButton3 = new QPushButton(frame);
        EmptyButton3->setObjectName("EmptyButton3");
        EmptyButton3->setGeometry(QRect(270, 10, 100, 32));
        EmptyButton3->setCursor(QCursor(Qt::PointingHandCursor));
        EmptyButton3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        RecordButton = new QPushButton(frame_2);
        RecordButton->setObjectName("RecordButton");
        RecordButton->setGeometry(QRect(340, 190, 101, 91));
        RecordButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color:  none;\n"
"    border: none;\n"
"}\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8("img/voice_btn.png"), QSize(), QIcon::Normal, QIcon::Off);
        RecordButton->setIcon(icon);
        RecordButton->setIconSize(QSize(90, 90));
        VoiceLabel = new QLabel(frame_2);
        VoiceLabel->setObjectName("VoiceLabel");
        VoiceLabel->setGeometry(QRect(0, 160, 801, 151));
        VoiceLabel->setPixmap(QPixmap(QString::fromUtf8("img/voice.png")));
        VoiceLabel->setScaledContents(true);
        VoiceLabel->setWordWrap(false);
        VoiceLabel->setOpenExternalLinks(false);
        VoiceLabel->raise();
        RecordButton->raise();

        verticalLayout->addWidget(frame_2);

        GuestMainWindow->setCentralWidget(centralwidget);

        retranslateUi(GuestMainWindow);

        QMetaObject::connectSlotsByName(GuestMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GuestMainWindow)
    {
        GuestMainWindow->setWindowTitle(QCoreApplication::translate("GuestMainWindow", "YourVoice", nullptr));
        LogInButton->setText(QCoreApplication::translate("GuestMainWindow", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        LogoLabel->setText(QString());
        EmptyButton1->setText(QCoreApplication::translate("GuestMainWindow", "btn_1", nullptr));
        EmptyButton2->setText(QCoreApplication::translate("GuestMainWindow", "btn_2", nullptr));
        EmptyButton3->setText(QCoreApplication::translate("GuestMainWindow", "btn_3", nullptr));
        RecordButton->setText(QString());
        VoiceLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GuestMainWindow: public Ui_GuestMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUESTMAINWINDOW_H
