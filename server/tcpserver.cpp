#include "tcpserver.h"
#include "threadhandle.h"
#include <QSqlError>
#include <QSqlQuery>

TcpServer::TcpServer(QObject *parent,int numConnections) :
    QTcpServer(parent)
{
     tcpClient = new  QHash<int,TcpSocket *>;
     setMaxPendingConnections(numConnections);

     //连接MySQL数据库
     QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
     db.setHostName("127.0.0.1");
     db.setUserName("root");
     db.setPassword("root");
     db.setDatabaseName("game2048");

     if(!db.open()){
         qDebug()<<"数据库连接失败:"<<db.lastError().text()<<endl;
         exit(0);
     }else{
         qDebug()<<"数据库连接成功"<<endl;
     }
     qDebug() << "客户端已启动"<<endl;
}

TcpServer::~TcpServer()
{
    emit this->sentDisConnect(-1);
    delete tcpClient;
}

void TcpServer::setMaxPendingConnections(int numConnections)
{
    //调用Qtcpsocket函数，设置最大连接数，主要是使maxPendingConnections()依然有效
    this->QTcpServer::setMaxPendingConnections(numConnections);
    this->maxConnections = numConnections;
}

void TcpServer::incomingConnection(qintptr socketDescriptor) //多线程必须在此函数里捕获新连接
{
    if (tcpClient->size() > maxPendingConnections())//继承重写此函数后，QTcpServer默认的判断最大连接数失效，自己实现
    {
        QTcpSocket tcp;
        tcp.setSocketDescriptor(socketDescriptor);
        tcp.disconnectFromHost();
        return;
    }

    //创建一个新的TcpSocket和线程处理该连接
    auto th = ThreadHandle::getClass().getThread();
    auto tcpTemp = new TcpSocket(socketDescriptor);
    QString ip =  tcpTemp->peerAddress().toString();
    qint16 port = tcpTemp->peerPort();

    //断开连接的处理，从列表移除，并释放断开的Tcpsocket，此槽必须实现，线程管理计数也是靠的他
    connect(tcpTemp,&TcpSocket::sockDisConnect,this,&TcpServer::sockDisConnectSlot);

    //断开信号
    connect(this,&TcpServer::sentDisConnect,tcpTemp,&TcpSocket::disConTcp);

    tcpTemp->moveToThread(th);//把tcp类移动到新的线程，从线程管理类中获取
    tcpClient->insert(socketDescriptor,tcpTemp);//插入到连接信息中
    emit connectClient(socketDescriptor,ip,port);
}

void TcpServer::sockDisConnectSlot(int handle,const QString & ip, quint16 prot,QThread * th)
{
    tcpClient->remove(handle);      //连接管理中移除断开连接的socket
    ThreadHandle::getClass().removeThread(th);  //告诉线程管理类哪个线程里的连接断开了
    emit sockDisConnect(handle,ip,prot);
}

void TcpServer::clear()
{
    emit this->sentDisConnect(-1);  //传参-1，清除所有连接
    ThreadHandle::getClass().clear();//清空线程池
    tcpClient->clear();             //清空map
}
