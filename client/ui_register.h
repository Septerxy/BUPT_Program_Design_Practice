/********************************************************************************
** Form generated from reading UI file 'register.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QPushButton *name;
    QTextEdit *inputName;
    QPushButton *passwd;
    QLineEdit *inputPswd;
    QPushButton *ready;
    QPushButton *back;
    QLineEdit *notice;

    void setupUi(QWidget *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName(QString::fromUtf8("Register"));
        Register->resize(681, 536);
        Register->setStyleSheet(QString::fromUtf8("background-image: url(:/pic/back3.jpg);"));
        name = new QPushButton(Register);
        name->setObjectName(QString::fromUtf8("name"));
        name->setGeometry(QRect(130, 100, 101, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        name->setFont(font);
        name->setFlat(true);
        inputName = new QTextEdit(Register);
        inputName->setObjectName(QString::fromUtf8("inputName"));
        inputName->setGeometry(QRect(270, 100, 271, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(14);
        inputName->setFont(font1);
        inputName->setTabChangesFocus(true);
        passwd = new QPushButton(Register);
        passwd->setObjectName(QString::fromUtf8("passwd"));
        passwd->setGeometry(QRect(130, 200, 101, 51));
        passwd->setFont(font);
        passwd->setFlat(true);
        inputPswd = new QLineEdit(Register);
        inputPswd->setObjectName(QString::fromUtf8("inputPswd"));
        inputPswd->setGeometry(QRect(270, 200, 271, 51));
        inputPswd->setFrame(false);
        ready = new QPushButton(Register);
        ready->setObjectName(QString::fromUtf8("ready"));
        ready->setGeometry(QRect(60, 320, 101, 51));
        ready->setFont(font);
        ready->setFlat(true);
        back = new QPushButton(Register);
        back->setObjectName(QString::fromUtf8("back"));
        back->setGeometry(QRect(490, 320, 101, 51));
        back->setFont(font);
        back->setFlat(true);
        notice = new QLineEdit(Register);
        notice->setObjectName(QString::fromUtf8("notice"));
        notice->setGeometry(QRect(270, 260, 181, 21));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Times New Roman"));
        notice->setFont(font2);
        notice->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        notice->setFrame(false);
        notice->setReadOnly(true);

        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QWidget *Register)
    {
        Register->setWindowTitle(QCoreApplication::translate("Register", "Form", nullptr));
        name->setText(QCoreApplication::translate("Register", "name", nullptr));
        inputName->setHtml(QCoreApplication::translate("Register", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Times New Roman'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Times New Roman'; font-size:12pt;\"><br /></p></body></html>", nullptr));
        passwd->setText(QCoreApplication::translate("Register", "Password", nullptr));
        ready->setText(QCoreApplication::translate("Register", "Register", nullptr));
        back->setText(QCoreApplication::translate("Register", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
