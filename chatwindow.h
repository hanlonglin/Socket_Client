#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QDateTime>
#include <QScrollBar>
#include "tcptools.h"


namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
     ChatWindow(QString name);
    ~ChatWindow();

     //属性
     QString nameTo;

     /*设置历史消息*/
      void setHisMessages(QList<Message> hislist);


private:
    Ui::ChatWindow *ui;

    //其他类属性
    TcpTools tcpTools;

private slots:

    /*发送*/
    void sendMesSlot();

    /*清空聊天记录*/
    void clearHisSlot();

    /*滚动最下面*/
    void roolToEndSlot();


    /*接受消息*/
    void receiveMesSlot(Message mes);


};

#endif // CHATWINDOW_H
