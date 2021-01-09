/*****************************************************************
 * Copyright (c)2020, by Septer(Xiong Yu), Beijing University of Posts and Telecommunication
 * All rights reserved.
 * FileName：		login.cpp
 * System：          	2048
 * SubSystem：        	2048
 * Author：		Septer(Xiong Yu)
 * Date：		2020.11.1
 * Version：		3.0
 * Description：
        定义Login类及类的成员函数
 *
 * Last Modified:

    2020.11.26, 	By Septer(Xiong Yu)
*****************************************************************/

#include "login.h"
#include "ui_login.h"
#include "functions.h"

#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QStyleOption>
#include <QPainter>
#include <QStyle>
#include <QString>
#include <WinSock2.h>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    this->setWindowTitle("Login");

    ui->inputPswd->setEchoMode(QLineEdit::Password); /* 设置输入模式为密码模式 */
}

Login::~Login()
{
    delete ui;

    delete tcpClient;
}

/////////////////////////////////////////////////////////////////////
// Function：		on_ready_clicked
// Description:
//	按下Ready键，请求登录
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Login::on_ready_clicked()
{
    this->tcpClient = new QTcpSocket(this);
    this->tcpClient->abort();

    connect(this->tcpClient,&QTcpSocket::readyRead,this,&Login::ReceiveData);

    connect(this->tcpClient,&QTcpSocket::disconnected,[](){qDebug()<< "Disconnected." ;});

    QString ipAdd(QString::fromStdString(SERVER_IP)); //10.128.221.5
    QString portd(QString::fromStdString(SERVER_PORT));
    qDebug()<<"No error";

    this->tcpClient->connectToHost(ipAdd,portd.toInt());

    if(this->tcpClient->waitForConnected())
    {
        qDebug()<<"System Ready!";
    }
    else
    { //连接失败则尝试重连
        qDebug()<<"Failed."<<this->tcpClient->errorString();

        while(!this->tcpClient->waitForConnected())
        {
            this->tcpClient->connectToHost(ipAdd,portd.toInt());
            qDebug()<<"Retry connectToHost.";
        }
        qDebug()<<"System Ready!";
    }

    char name[BUF_SIZE], pswd[BUF_SIZE]; /* 存储用户输入的用户名和密码 */
    strcpy(name,this->ui->inputName->toPlainText().toLatin1().data());
    strcpy(pswd,this->ui->inputPswd->text().toLatin1().data());
    qDebug()<<name;
    qDebug()<<pswd;

    if((strlen(name)==0) || (strlen(name)>10) || (strlen(pswd)==0) || (strlen(pswd)==0))
    {
        this->ui->notice->setPlaceholderText("用户名或密码不能为空");
    }
    else
    {
        /* 刷新buffer */
        ZeroMemory(buf, BUF_SIZE);

        /* 登录：Login 用户名 密码 */
        strcat(buf,"Login ");
        strcat(buf,name);
        strcat(buf," ");
        strcat(buf,pswd);
        qDebug()<<buf;

        strcpy(this->name,name);


        /* 向服务器发送数据 */
        this->tcpClient->write(QString::fromStdString(buf).toUtf8());

        if (SOCKET_ERROR == retVal)
        {
            qDebug() << "send failed !";
        }

        /* 刷新buffer */
        ZeroMemory(buf, BUF_SIZE);
    }

}

/////////////////////////////////////////////////////////////////////
// Function：		ReceiveData
// Description:
//	读取socket
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Login::ReceiveData()
{

    QString data = this->tcpClient->readAll();

    if(QString::compare(data,"quit")==0)
    {
        qDebug() << "quit!" << endl;
        this->close();
    }
    else if (QString::compare(data.mid(0,7),"success")==0)
    {
        this->ui->notice->setPlaceholderText("登录成功");

        this->ui->inputPswd->clear();
        this->ui->notice->clear();

        this->tcpClient->disconnectFromHost();
        this->tcpClient->close();

        this->hide();

        emit ShowGame(this->name,data.toLatin1().data());
    }
    else
    {
        this->ui->notice->setPlaceholderText("用户名或密码错误");

        this->tcpClient->disconnectFromHost();
        this->tcpClient->close();
    }
}

/////////////////////////////////////////////////////////////////////
// Function：		on_back_clicked
// Description:
//	按下Back键，回到widget界面
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Login::on_back_clicked()
{
    this->ui->inputPswd->clear();
    this->ui->notice->clear();

    this->hide();

    emit ShowMain();
}

/////////////////////////////////////////////////////////////////////
// Function：		ReceiveShowLogin
// Description:
//	接收展示Login界面信号的槽函数
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Login::ReceiveShowLogin()
{
    this->show();
}


void Login::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
