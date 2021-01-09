/*server的main函数*/
#include <QCoreApplication>
#include "tcpserver.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <iostream>
#include<QSqlDatabase>
#ifndef Q_OS_WIN
//#include "eventdispatcher_libev/eventdispatcher_libev.h"
#endif


int main(int argc, char *argv[])
{
    //qInstallMessageHandler(customMessageHandler);
#ifndef Q_OS_WIN
    QCoreApplication::setEventDispatcher(new EventDispatcherLibEv());
#endif
    QCoreApplication a(argc, argv);

    //开启服务端，监听9990端口
    TcpServer ser;
    ser.listen(QHostAddress::Any,9990);

    return a.exec();
}
