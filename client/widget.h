/*****************************************************************
 * Copyright (c)2020, by Septer(Xiong Yu), Beijing University of Posts and Telecommunication
 * All rights reserved.
 * FileName：		widget.h
 * System：          	2048
 * SubSystem：        	2048
 * Author：		Septer(Xiong Yu)
 * Date：		2020.11.1
 * Version：		3.0
 * Description：
        声明Widget类及类的成员函数
 *
 * Last Modified:

    2020.11.26, 	By Septer(Xiong Yu)
*****************************************************************/

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "functions.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    char buf[BUF_SIZE];   /* 用于接收数据缓冲区 */

    int retVal;    /* 调用各种Socket函数的返回值 */

    ~Widget();

private:
    Ui::Widget *ui;

protected:
void paintEvent(QPaintEvent *);

signals:
    void ShowRegister(); /* 展示注册界面 */

    void ShowLogin(); /* 展示登陆界面 */

private slots:
    void on_needRegis_clicked();

    void ReceiveShowMain();

    void on_needLogin_clicked();
};
#endif // WIDGET_H
