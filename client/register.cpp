/*****************************************************************
 * Copyright (c)2020, by Septer(Xiong Yu), Beijing University of Posts and Telecommunication
 * All rights reserved.
 * FileName：		register.cpp
 * System：          	2048
 * SubSystem：        	2048
 * Author：		Septer(Xiong Yu)
 * Date：		2020.11.1
 * Version：		3.0
 * Description：
        定义Register类及类的成员函数
 *
 * Last Modified:

    2020.11.26, 	By Septer(Xiong Yu)
*****************************************************************/

#include "register.h"
#include "ui_register.h"
#include "functions.h"

#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QStyleOption>
#include <QPainter>
#include <QStyle>
#include <QString>
#include <WinSock2.h>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{

    ui->setupUi(this);

    this->setWindowTitle("Register");

    ui->inputPswd->setEchoMode(QLineEdit::Password);
}

Register::~Register()
{
    delete ui;
    delete tcpClient;
}

void Register::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

/////////////////////////////////////////////////////////////////////
// Function：		ReceiveShowRegis
// Description:
//	接收展示Register界面信号的槽函数
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Register::ReceiveShowRegis()
{
    this->show();
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
void Register::on_back_clicked()
{
    this->ui->inputName->clear();
    this->ui->inputPswd->clear();
    this->ui->notice->clear();

    this->hide();

    emit ShowMain();
}

/////////////////////////////////////////////////////////////////////
// Function：		on_ready_clicked
// Description:
//	按下Ready键，请求注册
// Args：
//	无参
// Return Values:
//      int
//      是否正确发送请求注册信息
/////////////////////////////////////////////////////////////////////
int Register::on_ready_clicked()
{
    this->tcpClient = new QTcpSocket(this);
    this->tcpClient->abort();

    connect(this->tcpClient,&QTcpSocket::readyRead,this,&Register::ReceiveData);

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
    { /* 连接失败则尝试重连 */
        qDebug()<<"Failed."<<this->tcpClient->errorString();

        while(!this->tcpClient->waitForConnected())
        {
            this->tcpClient->connectToHost(ipAdd,portd.toInt());
            qDebug()<<"Retry connectToHost.";
        }
        qDebug()<<"System Ready!";
    }

    char name[BUF_SIZE], pswd[BUF_SIZE]; /* 存储输入的用户名，密码 */
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

        /*注册：Register 用户名 密码 */
        strcat(buf,"Register ");
        strcat(buf,name);
        strcat(buf," ");
        strcat(buf,pswd);
        qDebug()<<buf;


        //向服务器发送数据
        this->tcpClient->write(QString::fromStdString(buf).toUtf8());

        if (SOCKET_ERROR == retVal)
        {
            qDebug() << "send failed !";
        }

        /* 刷新buffer */
        ZeroMemory(buf, BUF_SIZE);
    }

    return 0;
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
void Register::ReceiveData()
{

    QString data = this->tcpClient->readAll();

    if(QString::compare(data,"quit")==0)
    {
        qDebug() << "quit!" << endl;

        this->close();
    }
    else if (QString::compare(data,"success")==0)
    {
        this->ui->notice->setPlaceholderText("注册成功");

        ui->inputName->clear();
        ui->inputPswd->clear();
        this->ui->notice->clear();

        this->tcpClient->disconnectFromHost();
        this->tcpClient->close();

        this->hide();

        emit ShowLogin();
    }
    else
    {
        this->ui->notice->setPlaceholderText("用户名已存在");

        this->tcpClient->disconnectFromHost();
        this->tcpClient->close();
    }
}
