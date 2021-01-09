/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTextEdit *info;
    QPushButton *needRegis;
    QPushButton *needLogin;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(683, 582);
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        Widget->setFont(font);
        Widget->setStyleSheet(QString::fromUtf8("background-image: url(:/pic/back2.jpg);"));
        info = new QTextEdit(Widget);
        info->setObjectName(QString::fromUtf8("info"));
        info->setGeometry(QRect(200, 100, 291, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(36);
        font1.setBold(false);
        font1.setWeight(50);
        info->setFont(font1);
        info->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        info->setReadOnly(true);
        needRegis = new QPushButton(Widget);
        needRegis->setObjectName(QString::fromUtf8("needRegis"));
        needRegis->setGeometry(QRect(90, 310, 131, 81));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Times New Roman"));
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        needRegis->setFont(font2);
        needRegis->setStyleSheet(QString::fromUtf8(""));
        needRegis->setFlat(true);
        needLogin = new QPushButton(Widget);
        needLogin->setObjectName(QString::fromUtf8("needLogin"));
        needLogin->setGeometry(QRect(460, 310, 131, 81));
        needLogin->setFont(font2);
        needLogin->setFlat(true);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        info->setHtml(QCoreApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Times New Roman'; font-size:36pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:18pt; font-weight:600; color:#fcfcfc;\">Welcome to 2048</span></p></body></html>", nullptr));
        needRegis->setText(QCoreApplication::translate("Widget", "Register", nullptr));
        needLogin->setText(QCoreApplication::translate("Widget", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
