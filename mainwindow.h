#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QInputDialog>
#include <QCloseEvent>

#include "chatwindow.h"

#define FRIENDS_NAME_FILE      "friend_list.ini"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    QList<Message> MessageList;  //消息队列

    QList<ChatWindow*> chatWindowList; //打开的聊天窗口

private:
    Ui::MainWindow *ui;
    //*********************接受消息
    QTcpServer *server;
    QTcpSocket *clientConnection;

    /*重写closeEvent函数*/
    void closeEvent(QCloseEvent *e);


private slots:

    /*添加好友*/
    void addFriendSlot();

    /*删除好友*/
    void delFriendSlot();

    /*显示好友,打开程序，刷新时调用*/
    void showFriendsSlot();

    /*保存好友，退出程序*/
    void saveFriendsSlot();

    /*打开聊天界面*/
    void openChartSlot(QListWidgetItem* item);

    //*********************接受消息

    /*服务端*/
    void acceptClientSlot();

    void readClientSlot();

signals:

    /*接收客户端消息*/
    void sendMesSignal(Message mes);


};

#endif // MAINWINDOW_H
