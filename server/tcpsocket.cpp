#include "tcpsocket.h"
#include <QtConcurrent/QtConcurrent>
#include <QHostAddress>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <QString>
#include <QFile>
#include <QTextCodec>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include <QDebug>

using namespace std;

TcpSocket::TcpSocket(qintptr socketDescriptor, QObject *parent) : //构造函数在主线程执行，lambda在子线程
    QTcpSocket(parent),socketID(socketDescriptor)
{
    this->setSocketDescriptor(socketDescriptor);

    //接收到消息时执行readData函数
    connect(this,&TcpSocket::readyRead,this,&TcpSocket::readData);

    //连接断开时通过sockDisConnect信号量通知TcpServer
    dis = connect(this,&TcpSocket::disconnected,
                  [&](){
        qDebug() << "disconnect" ;
        emit sockDisConnect(socketID,this->peerAddress().toString(),this->peerPort(),QThread::currentThread());//发送断开连接的用户信息
        this->deleteLater();
    });

    connect(&watcher,&QFutureWatcher<QByteArray>::finished,this,&TcpSocket::startNext);
    connect(&watcher,&QFutureWatcher<QByteArray>::canceled,this,&TcpSocket::startNext);
    qDebug() << "new connect" << endl;
}

TcpSocket::~TcpSocket()
{
}


void TcpSocket::sendData(const QByteArray &data, const int id)
{
    if(id == socketID)
    {
        write(data);
    }
    //this->QAbstractSocket::writeData("fadongxi",1024);
}

void TcpSocket::disConTcp(int i)
{
    if (i == socketID)
    {
        this->disconnectFromHost();//与客户端断开连接
    }
    else if (i == -1) //-1为全部断开
    {
        disconnect(dis); //先断开连接的信号槽，防止二次析构
        this->disconnectFromHost();
        this->deleteLater();
    }
}


void TcpSocket::readData()
{
    /*打印收到客户端的信息，时间和ip端口号等*/
    qDebug() << "----------------------------" << endl;
    auto data = QString::fromUtf8(this->readAll());
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ");
    qDebug() << qPrintable(currentTime) << endl;            //打印当前时间
    qDebug() << "Recv from Client [" << qPrintable(this->peerAddress().toString());//打印客户端IP地址
    qDebug() << ":"<< peerPort() << "] : " << data << endl; //打印端口号

    /*对收到信息进行处理*/
    QStringList splits=data.split(" "); //将收到的消息按空格分割
    QString msg="";

    /*处理注册请求*/
    if (splits[0] == "Register")
    {
        /*获得注册用户名和密码*/
        QString username = splits[1];
        QString password = splits[2];
        qDebug() << "收到注册请求..." << endl;
        qDebug() << "用户名：" << username << endl;
        qDebug() << "密码：" << password << endl;

        /*数据库的插入*/
        QString stmt = "insert into userinfo(username,password) values('" + username + "', '" + password + "')";
        query.prepare("insert into userinfo(username,password) values(?, ?)");
        query.addBindValue(username);
        query.addBindValue(password);

        /*判断是否成功*/
        if (query.exec())
        {
            qDebug() << "注册成功！" << endl;
            msg = "success";
        }
        else
        {
            qDebug() << "注册失败！" << endl;
            msg = "failed";
        }
    }

    /*处理登录请求*/
    else if (splits[0] == "Login") {
        /*获取登录的用户名和密码*/
        QString username = splits[1];
        QString password = splits[2];
        qDebug() << "收到登录请求..." << endl;
        qDebug() << "用户名：" << username << endl;
        qDebug() << "密码：" << password << endl;

        /*查询数据库*/
        query.prepare("select * from userinfo where username = ? and password = ?");
        query.addBindValue(username);
        query.addBindValue(password);

        /*判断是否查询成功*/
        if (query.exec())
        {
            if (query.first())  //若查到数据，说明用户名和密码正确
            {
                msg = "success ";
                /*获取该用户的矩阵、当前分数、最高分数*/
                QString matrix = query.value(3).toString();
                QString curScore = query.value(4).toString();
                QString topScore = query.value(5).toString();

                qDebug() << "矩阵:" << matrix << endl;
                qDebug() << "用户当前分数:" << curScore << endl;
                qDebug() << "用户最高分数:" << topScore << endl;
                msg += matrix + " " + curScore + " " + topScore + " ";

                /*查询游戏最高分*/
                query.exec("select max(`topScore`) from `userinfo`");

                /*判断查询是否成功*/
                if(query.first())
                {
                    QString gameTop = query.value(0).toString();		//获取最高分
                    qDebug() << "最高分：" << gameTop << endl;
                    msg +=gameTop;
                    qDebug()<<"登录成功！"<<endl;
                }
                else
                {
                    qDebug()<<"查询游戏最高分失败！"<<endl;
                    msg += "-1";
                }

            }
            else
            {
                qDebug() << "用户名或密码错误！" << endl;
                msg = "failed";
            }
        }
        else
        {
            qDebug() << "查询失败！" << endl;
            msg = "failed";
        }
    }

    /*处理存档请求*/
    else if (splits[0] == "Save")
    {
        /*获取存档用户名、矩阵和当前分数*/
        QString username = splits[1];
        QString matrix = splits[2];
        QString curScore = splits[3];
        qDebug() << "用户名：" << username << endl;
        qDebug() << "矩阵：" << matrix << endl;
        qDebug() << "当前分数：" << curScore << endl;

        /*查询该用户*/
        query.prepare("select topScore from userinfo where username = ?");
        query.addBindValue(username);
        query.exec();

        /*判断查询是否成功*/
        if(query.first())
        {
            QString topScore = query.value(0).toString();		//获取用户最高分
            QString newTop = QString::number(max(topScore.toInt(),curScore.toInt()));   //计算新最高分
            if(newTop.toInt()>topScore.toInt())
            {
                qDebug()<<"打破纪录，新最高分："<<newTop<<endl;
            }
            query.prepare("update userinfo "
                          "set matrix = ?, curScore = ?,topScore = ? "
                          "where username = ?");
            query.addBindValue(matrix);
            query.addBindValue(curScore);
            query.addBindValue(newTop);
            query.addBindValue(username);
            if (query.exec())
            {
                qDebug() << "存档成功！" << endl;
                msg = "success";
            }
            else
            {
                qDebug() << "存档失败！" << endl;
                msg = "failed";
            }
        }
        else
        {
            qDebug() << "该用户不存在！" << endl;
            msg = "failed";
        }
    }
    else
    {
        msg = "request not valid!";
        qDebug()<< "request not valid!"<< endl;
    }

    /*将msg用utf8编码后发送*/
    sendData(msg.toUtf8(),socketID);
    qDebug() << "----------------------------" << endl;
}

QByteArray TcpSocket::handleData(QByteArray data, const QString &ip, qint16 port)
{
    QTime time;
    time.start();

    QElapsedTimer tm;
    tm.start();
    while(tm.elapsed() < 100)
    {}
    data = ip.toUtf8() + " " + QByteArray::number(port) + " " + data + " " + QTime::currentTime().toString().toUtf8();
    return data;
}

void TcpSocket::startNext()
{
    this->write(watcher.future().result());
    if (!datas.isEmpty())
    {
        watcher.setFuture(QtConcurrent::run(this,&TcpSocket::handleData,datas.dequeue(),this->peerAddress().toString(),this->peerPort()));
    }
}
