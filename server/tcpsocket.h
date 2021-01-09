/*Server的通讯套接字*/
#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>
#include <QQueue>
#include <QFutureWatcher>
#include <QByteArray>
#include <QSqlQuery>

#include <QTime>


class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpSocket(qintptr socketDescriptor, QObject *parent = 0);
    ~TcpSocket();
    QByteArray handleData(QByteArray data,const QString & ip, qint16 port);//用来处理数据的函数

signals:
    //void readData(const int,const QString &,const quint16,const QByteArray &);

    /*断开连接的用户信息，此信号必须发出！线程管理类根据信号计数的*/
    void sockDisConnect(const int ,const QString &,const quint16, QThread *);

public slots:
    void sendData(const QByteArray & ,const int);//发送信号的槽
    void disConTcp(int i);  //断开TCP连接

protected slots:
    void readData();    //接收数据
    void startNext();   //处理下一个

protected:
    QFutureWatcher<QByteArray> watcher; //使用信号和槽监视 QFuture
    QQueue<QByteArray> datas;

private:
    QSqlQuery query;            //数据库操作对象
    qintptr socketID;
    QMetaObject::Connection dis;
};

#endif // TCPSOCKET_H
