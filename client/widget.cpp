/*****************************************************************
 * Copyright (c)2020, by Septer(Xiong Yu), Beijing University of Posts and Telecommunication
 * All rights reserved.
 * FileName：		widget.cpp
 * System：          	2048
 * SubSystem：        	2048
 * Author：		Septer(Xiong Yu)
 * Date：		2020.11.1
 * Version：		3.0
 * Description：
        定义Widget类及类的成员函数
 *
 * Last Modified:

    2020.11.26, 	By Septer(Xiong Yu)
*****************************************************************/

#include "widget.h"
#include "ui_widget.h"
#include "functions.h"

#include <QStyleOption>
#include <QPainter>
#include <QStyle>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("Start Up");

}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

/////////////////////////////////////////////////////////////////////
// Function：		on_needRegis_clicked
// Description:
//	按下Register按钮，前往注册
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Widget::on_needRegis_clicked()
{
    this->hide();

    emit ShowRegister();
}

/////////////////////////////////////////////////////////////////////
// Function：		ReceiveShowMain
// Description:
//	接收展示widget界面信号的槽函数
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Widget::ReceiveShowMain()
{
    this->show();
}

/////////////////////////////////////////////////////////////////////
// Function：		on_needLogin_clicked
// Description:
//	按下Login按钮，前往登录
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Widget::on_needLogin_clicked()
{
    this->hide();
    emit ShowLogin();
}
