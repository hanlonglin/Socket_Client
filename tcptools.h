#ifndef TCPTOOLS_H
#define TCPTOOLS_H

#include <QtNetwork/QtNetwork>
#include <QDebug>
#include <QObject>
#include "common.h"


class TcpTools:public QObject
{
    Q_OBJECT
public:
    TcpTools(); //address示例192.168.8.8:21
    ~TcpTools();

    /*发送信息*/
    int sendMsg(QString ip,QString mes);


private:

    //客户端
    QString ip;
    QTcpSocket *client;


};

#endif // TCPTOOLS_H
