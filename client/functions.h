/*****************************************************************
 * Copyright (c)2020, by Septer(Xiong Yu), Beijing University of Posts and Telecommunication
 * All rights reserved.
 * FileName：		functions.h
 * System：          	2048
 * SubSystem：        	2048
 * Author：		Septer(Xiong Yu)
 * Date：		2020.11.1
 * Version：		3.0
 * Description：
        包含需求的头文件
        宏定义全局变量和常数
 *
 * Last Modified:

    2020.11.26, 	By Septer(Xiong Yu)
*****************************************************************/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDebug>
#include <tchar.h>
#include <iostream>
#include <WinSock2.h>
#include <string>
#include <time.h>   /* 包含设定随机数种子所需要的time()函数 */
#include <stdio.h>  /* 包含C的IO读写功能 */
#include <stdlib.h> /* 包含C标准库的功能 */

/* 包含Windows平台相关函数，包括控制台界面清屏及光标设定等功能 */
#include <conio.h>
#include <windows.h>
#include <io.h>
#include <direct.h>
#include <Shlobj.h>

/* 包含Linux平台相关函数，包括控制台界面清屏及光标设定等功能 */
#include <unistd.h>
#include <signal.h>

/* 宏定义 */
#define BUF_SIZE  64 /* 缓冲区大小 */

#define NUMSIZE 4 /* 2048行列数 */

#define REGIS "Register"
#define LOGIN "Login"

#pragma comment (lib,"ws2_32.lib") /* 加载WinSock */

#define SERVER_IP "10.128.221.51" /* 服务器IP */
#define SERVER_PORT "9990" /* 服务器端口 */



#endif // FUNCTIONS_H
