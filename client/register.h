/*****************************************************************
 * Copyright (c)2020, by Septer(Xiong Yu), Beijing University of Posts and Telecommunication
 * All rights reserved.
 * FileName：		register.h
 * System：          	2048
 * SubSystem：        	2048
 * Author：		Septer(Xiong Yu)
 * Date：		2020.11.1
 * Version：		3.0
 * Description：
        声明Register类及类的成员函数
 *
 * Last Modified:

    2020.11.26, 	By Septer(Xiong Yu)
*****************************************************************/

#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <WinSock2.h>
#include <QTcpSocket>
#include "functions.h"

namespace Ui
{
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);

    ~Register();


    char buf[BUF_SIZE];   /* 用于接收数据缓冲区 */

    int retVal;    /* 调用各种Socket函数的返回值 */

    QTcpSocket * tcpClient; /* TCP连接 */

private:
    Ui::Register *ui;

    void paintEvent(QPaintEvent *);

signals:
    void ShowMain(); /* 展示widget界面 */

    void ShowLogin(); /* 展示登录界面 */

public slots:
    void ReceiveShowRegis(); /* 接收展示Register界面信号的槽函数 */

    void ReceiveData();/* 获取服务器的反馈信息来判断有没有用户名/密码错误，能否正常注册 */

private slots:
    void on_back_clicked();

    int on_ready_clicked();
};

#endif // REGISTER_H
