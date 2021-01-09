/*****************************************************************
 * Copyright (c)2020, by Septer(Xiong Yu), Beijing University of Posts and Telecommunication
 * All rights reserved.
 * FileName：		game.h
 * System：          	2048
 * SubSystem：        	2048
 * Author：		Septer(Xiong Yu)
 * Date：		2020.11.1
 * Version：		3.0
 * Description：
        声明Game类及类的成员函数
 *
 * Last Modified:

    2020.11.26, 	By Septer(Xiong Yu)
*****************************************************************/

#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QTcpSocket>
#include <QKeyEvent>
#include "functions.h"

namespace Ui
{
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);

    ~Game();

    void ResetGame();   /* 重置游戏 */

    void MoveLeft();  /* 左移 */

    void MoveRight(); /* 右移 */

    void MoveUp();    /* 上移 */

    void MoveDown();  /* 下移 */

    void AddRandNum();    /* 生成随机数，本程序中仅生成2或4，概率之比设为9:1 */

    void CheckGameOver(); /* 检测是否输掉游戏，设定游戏结束标志 */

    int GetNullCount();   /* 获取游戏面板上空位置数量 */

    void ClearScreen();    /* 清屏 */

    void RefreshShow();    /* 刷新界面显示 */

    int Save();   /* 将当前用户信息存档 */


    char buf[BUF_SIZE];   /* 用于接收数据缓冲区 */

    int retVal;    /* 调用各种Socket函数的返回值 */

    QTcpSocket * tcpClient; /* TCP连接 */

    char userName[BUF_SIZE]; /* 当前用户名 */

    int board[NUMSIZE][NUMSIZE];     /* 游戏数字面板，抽象为二维数组 */

    int temp[NUMSIZE][NUMSIZE]; /* 用户云端存储的数据 */

    int score;           /* 游戏得分 */

    int tempScore;       /* 云端上次退出时分数 */

    int yourBest;        /* 该用户最高分 */

    int best;            /* 游戏最高分 */

    int ifNeedAddNum; /* 是否需要生成随机数标志，1表示需要，0表示不需要 */

    int ifGameOver;    /* 是否游戏结束标志，1表示游戏结束，0表示正常 */

    int if_prepare_exit; /* 是否准备退出游戏，1表示是，0表示否 */


signals:
    void ShowMain(); /* 返回主界面 */

public slots:
    void ReceiveShowGame(char *name, char *data); /* 接收展示游戏界面 */

    void ReceiveData();/* 获取服务器的反馈信息来判断有没有存档成功 */


private slots:
    void on_end_clicked();

    void on_newStart_clicked();

    void on_up_clicked();

    void on_left_clicked();

    void on_right_clicked();

    void on_down_clicked();

    void on_reload_clicked();

    void on_save_clicked();

private:
    Ui::Game *ui;

    void paintEvent(QPaintEvent *);
};

#endif // GAME_H
