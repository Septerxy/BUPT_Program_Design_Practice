/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QPushButton *ready;
    QPushButton *passwd;
    QLineEdit *inputPswd;
    QTextEdit *inputName;
    QLineEdit *notice;
    QPushButton *name;
    QPushButton *back;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(677, 591);
        Login->setStyleSheet(QString::fromUtf8("background-image: url(:/pic/back1.jpg);"));
        ready = new QPushButton(Login);
        ready->setObjectName(QString::fromUtf8("ready"));
        ready->setGeometry(QRect(40, 310, 101, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        ready->setFont(font);
        ready->setFlat(true);
        passwd = new QPushButton(Login);
        passwd->setObjectName(QString::fromUtf8("passwd"));
        passwd->setGeometry(QRect(110, 190, 101, 51));
        passwd->setFont(font);
        passwd->setFlat(true);
        inputPswd = new QLineEdit(Login);
        inputPswd->setObjectName(QString::fromUtf8("inputPswd"));
        inputPswd->setGeometry(QRect(250, 190, 271, 51));
        inputPswd->setFrame(false);
        inputName = new QTextEdit(Login);
        inputName->setObjectName(QString::fromUtf8("inputName"));
        inputName->setGeometry(QRect(250, 90, 271, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(14);
        inputName->setFont(font1);
        inputName->setTabChangesFocus(true);
        notice = new QLineEdit(Login);
        notice->setObjectName(QString::fromUtf8("notice"));
        notice->setGeometry(QRect(250, 250, 181, 21));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Times New Roman"));
        notice->setFont(font2);
        notice->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        notice->setFrame(false);
        notice->setReadOnly(true);
        name = new QPushButton(Login);
        name->setObjectName(QString::fromUtf8("name"));
        name->setGeometry(QRect(110, 90, 101, 51));
        name->setFont(font);
        name->setFlat(true);
        back = new QPushButton(Login);
        back->setObjectName(QString::fromUtf8("back"));
        back->setGeometry(QRect(470, 310, 101, 51));
        back->setFont(font);
        back->setFlat(true);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Form", nullptr));
        ready->setText(QCoreApplication::translate("Login", "Login", nullptr));
        passwd->setText(QCoreApplication::translate("Login", "Password", nullptr));
        inputName->setHtml(QCoreApplication::translate("Login", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Times New Roman'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Times New Roman'; font-size:12pt;\"><br /></p></body></html>", nullptr));
        name->setText(QCoreApplication::translate("Login", "name", nullptr));
        back->setText(QCoreApplication::translate("Login", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
