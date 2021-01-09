/*****************************************************************
 * Copyright (c)2020, by Septer(Xiong Yu), Beijing University of Posts and Telecommunication
 * All rights reserved.
 * FileName：		login.h
 * System：          	2048
 * SubSystem：        	2048
 * Author：		Septer(Xiong Yu)
 * Date：		2020.11.1
 * Version：		3.0
 * Description：
        声明Login类及类的成员函数
 *
 * Last Modified:

    2020.11.26, 	By Septer(Xiong Yu)
*****************************************************************/

#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QTcpSocket>
#include <QString>

#include "functions.h"

namespace Ui
{
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

    ~Login();

    char buf[BUF_SIZE];   /* 用于接收数据缓冲区 */

    int retVal;    /* 调用各种Socket函数的返回值 */

    QTcpSocket * tcpClient; /* TCP连接 */

    char name[BUF_SIZE]; /* 存储登录用户名 */

signals:
    void ShowMain(); /* 展示widget界面 */

    void ShowGame(char *name, char *data); /* 展示Game界面 */

public slots:
    void ReceiveShowLogin(); /* 接收展示登录界面的槽函数 */

    void ReceiveData(); /* 获取服务器的反馈信息来判断有没有用户名/密码错误，能否正常登录 */

private slots:
    void on_ready_clicked();

    void on_back_clicked();

private:
    Ui::Login *ui;

    void paintEvent(QPaintEvent *);
};

#endif // LOGIN_H
