#include "tcptools.h"

TcpTools::TcpTools()
{
    client=new QTcpSocket;

}
TcpTools::~TcpTools()
{
    if(client->isOpen())
        client->close();
    delete client;
}

/*发送消息*/
int TcpTools::sendMsg(QString address,QString mes)
{
    if(client->isOpen())
        client->close();
    ip=address;
    client->connectToHost(QHostAddress(ip),PORT);
    qDebug()<<"client state: "<<client->state();
    client->write(mes.toStdString().c_str());
    return 1;
}

