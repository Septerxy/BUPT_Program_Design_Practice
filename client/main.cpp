/*****************************************************************
 * Copyright (c)2020, by Septer(Xiong Yu), Beijing University of Posts and Telecommunication
 * All rights reserved.
 * FileName：		main.cpp
 * System：          	2048
 * SubSystem：        	2048
 * Author：		Septer(Xiong Yu)
 * Date：		2020.11.1
 * Version：		3.0
 * Description：
        初始化所有窗体
        定义窗体间信号与槽机制
        确立观察者模式
 *
 * Last Modified:

    2020.11.26, 	By Septer(Xiong Yu)
*****************************************************************/

#include "widget.h"
#include "register.h"
#include "login.h"
#include "game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;

    Register r;

    Login l;

    Game g;

    w.show();

    QObject::connect(&w,SIGNAL(ShowRegister()),&r,SLOT(ReceiveShowRegis()));
    QObject::connect(&r,SIGNAL(ShowMain()),&w,SLOT(ReceiveShowMain()));

    QObject::connect(&r,SIGNAL(ShowLogin()),&l,SLOT(ReceiveShowLogin()));

    QObject::connect(&w,SIGNAL(ShowLogin()),&l,SLOT(ReceiveShowLogin()));
    QObject::connect(&l,SIGNAL(ShowMain()),&w,SLOT(ReceiveShowMain()));

    QObject::connect(&l,SIGNAL(ShowGame(char*,char*)),&g,SLOT(ReceiveShowGame(char *,char *)));

    QObject::connect(&g,SIGNAL(ShowMain()),&w,SLOT(ReceiveShowMain()));

    return a.exec();
}
