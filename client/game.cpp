/*****************************************************************
 * Copyright (c)2020, by Septer(Xiong Yu), Beijing University of Posts and Telecommunication
 * All rights reserved.
 * FileName：		game.cpp
 * System：          	2048
 * SubSystem：        	2048
 * Author：		Septer(Xiong Yu)
 * Date：		2020.11.1
 * Version：		3.0
 * Description：
        定义Game类及类的成员函数
 *
 * Last Modified:

    2020.11.26, 	By Septer(Xiong Yu)
*****************************************************************/

#include "game.h"
#include "ui_game.h"
#include "functions.h"

#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QStyleOption>
#include <QPainter>
#include <QStyle>
#include <QString>
#include <QPalette>
#include <QStringList>
#include <WinSock2.h>

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);

    this->setWindowTitle("Game");
}

Game::~Game()
{
    delete ui;

    delete tcpClient;
}

/////////////////////////////////////////////////////////////////////
// Function：		ReceiveShowGame
// Description:
//	接收展示Game界面的信号的槽函数
// Args：
//	Arg1	char*  登录时的用户名
//	Arg2	char*  登录后服务器返回的数据
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::ReceiveShowGame(char *name,char *data)
{

    strcpy(this->userName,name);

    /* login的回复：success 数组[4][4]以逗号为间隔 用户当前分数 用户最高分 游戏最高分 */
    QString tempData = data;
    QStringList list = tempData.split(" ");
    this->tempScore=list[2].toInt();
    this->yourBest=list[3].toInt();
    this->best=list[4].toInt();

    QString dataNum=list[1]; //存储数组的子段
    QStringList dataList = dataNum.split(",");
    for(int i=0;i<NUMSIZE*NUMSIZE;i++)
    {
        this->temp[i/NUMSIZE][i%NUMSIZE]=dataList[i].toInt();
    }

    ui->name->setText(QString::fromStdString(this->userName));
    ui->bestScore->setText(QString::number(this->yourBest,10));
    ui->gameBest->setText(QString::number(this->best,10));

    this->show();
}

/////////////////////////////////////////////////////////////////////
// Function：		on_end_clicked
// Description:
//	按下end按钮返回widget界面
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::on_end_clicked()
{
    ClearScreen();

    this->hide();

    emit ShowMain(); /* 激活ShowMain()信号 */
}

void Game::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);

    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


/////////////////////////////////////////////////////////////////////
// Function：		ReceiveData
// Description:
//	监听来自服务器的信息
//  如果是quit，就将该窗体关闭
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::ReceiveData()
{

    QString data = this->tcpClient->readAll();

    if(QString::compare(data,"quit")==0)
    {
        qDebug() << "quit!" << endl;
        this->close();
    }

}

/////////////////////////////////////////////////////////////////////
// Function：		ResetGame
// Description:
//	重置游戏
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::ResetGame()
{
    score = 0;
    ifNeedAddNum = 1;
    ifGameOver = 0;
    if_prepare_exit = 0;

    /* 了解到游戏初始化时出现的两个数一定会有个2，所以先随机生成一个2，其他均为0 */
    int n = rand() % (NUMSIZE* NUMSIZE);

    int i;
    for (i = 0; i < NUMSIZE; ++i)
    {
        int j;
        for (j = 0; j < NUMSIZE; ++j)
        {
            board[i][j] = (n-- == 0 ? 2 : 0);
        }
    }

    /* 前面已经生成了一个2，这里再生成一个随机的2或者4，概率之比9:1 */
    AddRandNum();

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
            qDebug()<<board[i][j]<<" ";
        qDebug()<<endl;
    }

    /* 在这里刷新界面并显示的时候，界面上已经默认出现了两个数字，其他的都为空（值为0） */
    RefreshShow();
}

/////////////////////////////////////////////////////////////////////
// Function：		AddRandNum
// Description:
//	生成随机数
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::AddRandNum()
{
    srand((unsigned int)time(0));
    int n = rand() % GetNullCount(); /* 确定在何处空位置生成随机数 */

    int i;
    for (i = 0; i < NUMSIZE; ++i)
    {
        int j;
        for (j = 0; j < NUMSIZE; ++j)
        {
            /* 定位待生成的位置 */
            if (board[i][j] == 0 && n-- == 0)
            {
                board[i][j] = (rand() % 10 ? 2 : 4); /* 生成数字2或4，生成概率为9:1 */
                return;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////
// Function：		AddRandNum
// Description:
//	获取空位置数量
// Args：
//	无参
// Return Values:
//      int
//      空位置数量
/////////////////////////////////////////////////////////////////////
int Game::GetNullCount()
{
    int n = 0;

    int i;
    for (i = 0; i < NUMSIZE; ++i)
    {
        int j;
        for (j = 0; j < NUMSIZE; ++j)
        {
            board[i][j] == 0 ? ++n : 1;
        }
    }

    return n;
}

/////////////////////////////////////////////////////////////////////
// Function：		CheckGameOver
// Description:
//	检查游戏是否结束
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::CheckGameOver()
{
    int i;
    for (i = 0; i < NUMSIZE; ++i)
    {
        int j;
        for (j = 0; j < NUMSIZE-1; ++j)
        {
            /* 横向和纵向比较挨着的两个元素是否相等，若有相等则游戏不结束 */
            if (board[i][j] == board[i][j + 1] || board[j][i] == board[j + 1][i])
            {
                ifGameOver = 0;
                return;
            }
        }
    }

    ifGameOver = 1;
}


/*
 * 如下四个函数，实现上下左右移动时数字面板的变化算法
 * 左和右移动的本质一样，区别仅仅是列项的遍历方向相反
 * 上和下移动的本质一样，区别仅仅是行项的遍历方向相反
 * 左和上移动的本质也一样，区别仅仅是遍历时行和列互换
*/

/////////////////////////////////////////////////////////////////////
// Function：		MoveLeft
// Description:
//	左移
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::MoveLeft()
{
    /* 变量i用来遍历行项的下标，并且在移动时所有行相互独立，互不影响 */
    int i;
    for (i = 0; i < NUMSIZE; ++i)
    {
        /* 变量j为列下标，变量k为待比较（合并）项的下标，循环进入时k<j */
        int j, k;
        for (j = 1, k = 0; j < NUMSIZE; ++j)
        {
            if (board[i][j] > 0) /* 找出k后面第一个不为空的项，下标为j，之后分三种情况 */
            {
                if (board[i][k] == board[i][j])
                {
                    /* 情况1：k项和j项相等，此时合并方块并计分 */
                    score += board[i][k++] *= 2;
                    board[i][j] = 0;
                    ifNeedAddNum = 1; /* 需要生成随机数和刷新界面 */
                }

                else if (board[i][k] == 0)
                {
                    /* 情况2：k项为空，则把j项赋值给k项，相当于j方块移动到k方块 */
                    board[i][k] = board[i][j];
                    board[i][j] = 0;
                    ifNeedAddNum = 1;
                }

                else
                {
                    /* 情况3：k项不为空，且和j项不相等，此时把j项赋值给k+1项，相当于移动到k+1的位置 */
                    board[i][++k] = board[i][j];
                    if (j != k)
                    {
                        /* 判断j项和k项是否原先就挨在一起，若不是则把j项赋值为空（值为0） */
                        board[i][j] = 0;
                        ifNeedAddNum = 1;
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////
// Function：		MoveRight
// Description:
//	右移
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::MoveRight()
{
    /* 仿照左移操作，区别仅仅是j和k都反向遍历 */
    int i;
    for (i = 0; i < NUMSIZE; ++i)
    {
        int j, k;
        for (j = 2, k = 3; j >= 0; --j)
        {
            if (board[i][j] > 0)
            {
                if (board[i][k] == board[i][j])
                {
                    score += board[i][k--] *= 2;
                    board[i][j] = 0;
                    ifNeedAddNum = 1;
                }

                else if (board[i][k] == 0)
                {
                    board[i][k] = board[i][j];
                    board[i][j] = 0;
                    ifNeedAddNum = 1;
                }

                else
                {
                    board[i][--k] = board[i][j];
                    if (j != k)
                    {
                        board[i][j] = 0;
                        ifNeedAddNum = 1;
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////
// Function：		MoveUp
// Description:
//	上移
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::MoveUp()
{
    /* 仿照左移操作，区别仅仅是行列互换后遍历 */
    int i;
    for (i = 0; i < NUMSIZE; ++i)
    {
        int j, k;
        for (j = 1, k = 0; j < NUMSIZE; ++j)
        {
            if (board[j][i] > 0)
            {
                if (board[k][i] == board[j][i])
                {
                    score += board[k++][i] *= 2;
                    board[j][i] = 0;
                    ifNeedAddNum = 1;
                }

                else if (board[k][i] == 0)
                {
                    board[k][i] = board[j][i];
                    board[j][i] = 0;
                    ifNeedAddNum = 1;
                }

                else
                {
                    board[++k][i] = board[j][i];
                    if (j != k)
                    {
                        board[j][i] = 0;
                        ifNeedAddNum = 1;
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////
// Function：		MoveDown
// Description:
//	下移
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::MoveDown()
{
    /* 仿照左移操作，区别仅仅是行列互换后遍历，且j和k都反向遍历 */
    int i;
    for (i = 0; i < NUMSIZE; ++i)
    {
        int j, k;
        for (j = 2, k = 3; j >= 0; --j)
        {
            if (board[j][i] > 0)
            {
                if (board[k][i] == board[j][i])
                {
                    score += board[k--][i] *= 2;
                    board[j][i] = 0;
                    ifNeedAddNum = 1;
                }

                else if (board[k][i] == 0)
                {
                    board[k][i] = board[j][i];
                    board[j][i] = 0;
                    ifNeedAddNum = 1;
                }

                else
                {
                    board[--k][i] = board[j][i];
                    if (j != k)
                    {
                        board[j][i] = 0;
                        ifNeedAddNum = 1;
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////
// Function：		ClearScreen
// Description:
//	清屏
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::ClearScreen()
{
    ui->name->clear();
    ui->currentScore->clear();
    ui->bestScore->clear();
    ui->gameBest->clear();

    ui->tac_1->setText("");
    ui->tac_2->setText("");
    ui->tac_3->setText("");
    ui->tac_4->setText("");
    ui->tac_5->setText("");
    ui->tac_6->setText("");
    ui->tac_7->setText("");
    ui->tac_8->setText("");
    ui->tac_9->setText("");
    ui->tac_10->setText("");
    ui->tac_11->setText("");
    ui->tac_12->setText("");
    ui->tac_13->setText("");
    ui->tac_14->setText("");
    ui->tac_15->setText("");
    ui->tac_16->setText("");

}

/////////////////////////////////////////////////////////////////////
// Function：		RefreshShow
// Description:
//	更新界面展示
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::RefreshShow()
{
    ClearScreen();

    ui->name->setText(this->userName);

    ui->currentScore->setText(QString::number(this->score,10));
    ui->bestScore->setText(QString::number(this->yourBest,10));
    ui->gameBest->setText(QString::number(this->best,10));

    ui->tac_1->setText(QString::number(board[0][0],10));
    ui->tac_2->setText(QString::number(board[0][1],10));
    ui->tac_3->setText(QString::number(board[0][2],10));
    ui->tac_4->setText(QString::number(board[0][3],10));
    ui->tac_5->setText(QString::number(board[1][0],10));
    ui->tac_6->setText(QString::number(board[1][1],10));
    ui->tac_7->setText(QString::number(board[1][2],10));
    ui->tac_8->setText(QString::number(board[1][3],10));
    ui->tac_9->setText(QString::number(board[2][0],10));
    ui->tac_10->setText(QString::number(board[2][1],10));
    ui->tac_11->setText(QString::number(board[2][2],10));
    ui->tac_12->setText(QString::number(board[2][3],10));
    ui->tac_13->setText(QString::number(board[3][0],10));
    ui->tac_14->setText(QString::number(board[3][1],10));
    ui->tac_15->setText(QString::number(board[3][2],10));
    ui->tac_16->setText(QString::number(board[3][3],10));
}

/////////////////////////////////////////////////////////////////////
// Function：		on_newStart_clicked
// Description:
//	按下NewStart按键，重置游戏
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::on_newStart_clicked()
{
    ResetGame();
}

/////////////////////////////////////////////////////////////////////
// Function：		on_up_clicked
// Description:
//	按下↑按键，上移
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::on_up_clicked()
{
    MoveUp();

    /* 打破得分纪录 */
    if (score >yourBest)
    {
        yourBest = score;
    }

    if(score >best)
    {
        best=score;
    }

    /* 默认为需要生成随机数时也同时需要刷新显示，反之亦然 */
    if (ifNeedAddNum)
    {
        AddRandNum();
        RefreshShow();
    }
    else if (if_prepare_exit)
    {
        RefreshShow();
    }
}

/////////////////////////////////////////////////////////////////////
// Function：		on_left_clicked
// Description:
//	按下←按键，左移
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::on_left_clicked()
{
    MoveLeft();

    /* 打破得分纪录 */
    if (score >yourBest)
    {
        yourBest = score;
    }

    if(score >best)
    {
        best=score;
    }

    /* 默认为需要生成随机数时也同时需要刷新显示，反之亦然 */
    if (ifNeedAddNum)
    {
        AddRandNum();
        RefreshShow();
    }
    else if (if_prepare_exit)
    {
        RefreshShow();
    }
}

/////////////////////////////////////////////////////////////////////
// Function：		on_right_clicked
// Description:
//	按下→按键，右移
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::on_right_clicked()
{
    MoveRight();

    /* 打破得分纪录 */
    if (score >yourBest)
    {
        yourBest = score;
    }

    if(score >best)
    {
        best=score;
    }

    /* 默认为需要生成随机数时也同时需要刷新显示，反之亦然 */
    if (ifNeedAddNum)
    {
        AddRandNum();
        RefreshShow();
    }
    else if (if_prepare_exit)
    {
        RefreshShow();
    }
}

/////////////////////////////////////////////////////////////////////
// Function：		on_down_clicked
// Description:
//	按下↓按键，下移
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::on_down_clicked()
{
    MoveDown();

    /* 打破得分纪录 */
    if (score >yourBest)
    {
        yourBest = score;
    }

    if(score >best)
    {
        best=score;
    }

    /* 默认为需要生成随机数时也同时需要刷新显示，反之亦然 */
    if (ifNeedAddNum)
    {
        AddRandNum();
        RefreshShow();
    }
    else if (if_prepare_exit)
    {
        RefreshShow();
    }
}

/////////////////////////////////////////////////////////////////////
// Function：		on_reload_clicked
// Description:
//	按下Reload按键，恢复云端存储的数据
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::on_reload_clicked()
{
    score = tempScore;
    ifNeedAddNum = 1;
    ifGameOver = 0;
    if_prepare_exit = 0;

    for(int i=0;i<NUMSIZE;i++)
    {
        for(int j=0;j<NUMSIZE;j++)
            board[i][j]=temp[i][j];
    }

    RefreshShow();
}

/////////////////////////////////////////////////////////////////////
// Function：		on_save_clicked
// Description:
//	按下Save按键，将当前数据存档到云端
// Args：
//	无参
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Game::on_save_clicked()
{
    /* 将临时信息也更改 */
    this->tempScore=this->score;
    for(int i=0;i<NUMSIZE;i++)
    {
        for(int j=0;j<NUMSIZE;j++)
        {
            temp[i][j]=board[i][j];
        }
    }

    this->tcpClient = new QTcpSocket(this);
    this->tcpClient->abort();

    connect(this->tcpClient,&QTcpSocket::readyRead,this,&Game::ReceiveData);

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


    /* 刷新buffer */
    ZeroMemory(buf, BUF_SIZE);

    /* 保存：Save 用户名 数组[4][4]以逗号为间隔 用户当前分数 用户最高分 游戏最高分 */
    strcat(buf,"Save ");
    strcat(buf,this->userName);
    strcat(buf," ");

    for(int i=0;i<NUMSIZE-1;i++)
    {
        for(int j=0;j<NUMSIZE;j++)
        {
            strcat(buf,QString::number(this->board[i][j],10).toLatin1().data());
            strcat(buf,",");
        }
    }

    strcat(buf,QString::number(this->board[3][0],10).toLatin1().data());
    strcat(buf,",");
    strcat(buf,QString::number(this->board[3][1],10).toLatin1().data());
    strcat(buf,",");
    strcat(buf,QString::number(this->board[3][2],10).toLatin1().data());
    strcat(buf,",");
    strcat(buf,QString::number(this->board[3][3],10).toLatin1().data());
    strcat(buf," ");
    strcat(buf,QString::number(this->score,10).toLatin1().data());
    qDebug()<<buf;


    /* 向服务器发送数据 */
    this->tcpClient->write(QString::fromStdString(buf).toUtf8());

    if (SOCKET_ERROR == retVal)
    {
        qDebug() << "send failed !";
    }

    /* 刷新buffer */
    ZeroMemory(buf, BUF_SIZE);

    /* 断开连接 */
    this->tcpClient->disconnectFromHost();
    this->tcpClient->close();

}
