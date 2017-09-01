#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置标题
    setWindowTitle(QString::fromLocal8Bit("自制聊天工具"));
    setWindowIcon(QIcon("./qq.ico"));

    //链接
    connect(ui->pushButtonAdd,SIGNAL(clicked(bool)),this,SLOT(addFriendSlot())); //添加好友
    connect(ui->pushButtonDel,SIGNAL(clicked(bool)),this,SLOT(delFriendSlot()));//删除好友

    connect(ui->listWidgetFriends,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(openChartSlot(QListWidgetItem*)));//打开聊天界面
    //显示好友
    showFriendsSlot();

    //开始监听对方传来的信息
    server = new QTcpServer;
    if(server->listen(QHostAddress::Any,PORT))   //QHostAddress::Any表示任何ip
    {
        connect(server,SIGNAL(newConnection()),this,SLOT(acceptClientSlot()));//接受新的客户端链接
    }else{
        QMessageBox::information(this,"","无法接收信息，监听失败！");
    }


}

MainWindow::~MainWindow()
{
    saveFriendsSlot();

    if(clientConnection->isOpen())
        clientConnection->close();
    if(server->isListening())
        server->close();
    delete ui;
}

/*重写closeEvent()*/
void MainWindow::closeEvent(QCloseEvent *e)
{
    for(int i=0;i<chatWindowList.size();i++)
    {
        chatWindowList.at(i)->close();
    }
}

//*****************************************************************slots

/*添加好友*/
void MainWindow::addFriendSlot()
{
    QString name = QInputDialog::getText(this,QString::fromLocal8Bit("添加好友"),QString::fromLocal8Bit("请输入好友ip:"));
    if(name.isEmpty()) return ;
    QListWidgetItem *item=new QListWidgetItem(name);
    ui->listWidgetFriends->addItem(item);
    ui->listWidgetFriends->editItem(item);
}
/*删除好友*/
void MainWindow::delFriendSlot()
{
    for(int i=0;i<ui->listWidgetFriends->count();i++)
    {
        if(ui->listWidgetFriends->item(i)->isSelected())
            delete ui->listWidgetFriends->item(i);
    }
}
/*显示好友*/
void MainWindow::showFriendsSlot()
{
    QSettings *setting=new QSettings(FRIENDS_NAME_FILE,QSettings::IniFormat);
    setting->setIniCodec("UTF8");
    setting->beginGroup("FRIENDS");
    for(int i=0;i<setting->childKeys().count();i++)
    {
        ui->listWidgetFriends->addItem(new QListWidgetItem(setting->value(setting->childKeys().at(i)).toString()));
    }
    setting->endGroup();
    delete setting;

}
/*保存好友*/
void MainWindow::saveFriendsSlot()
{
    QSettings *setting=new QSettings(FRIENDS_NAME_FILE,QSettings::IniFormat);
    setting->clear();
    setting->setIniCodec("UTF8");
    setting->beginGroup("FRIENDS");
    for(int i=0;i<ui->listWidgetFriends->count();i++)
    {
        QString name=ui->listWidgetFriends->item(i)->text();
        setting->setValue(QString::number(i),name);
    }
    setting->endGroup();
    delete setting;
}


/*打开聊天界面*/
void MainWindow::openChartSlot(QListWidgetItem* item)
{
    bool isOpened=false;
    for(int i=0;i<chatWindowList.count();i++)
    {
        if(item->text()==chatWindowList.at(i)->nameTo)
        {
            chatWindowList.at(i)->show();
            isOpened=true;
            qDebug()<<"is opened ..";
        }
    }
    if(!isOpened)
    {
        QList<Message> hislist;
        for(int i=0;i<MessageList.count();i++)
        {
            if(MessageList.at(i).name==item->text())
                hislist.push_back(MessageList.at(i));
        }
        ChatWindow *chatWindow=new ChatWindow(item->text());
        connect(this,SIGNAL(sendMesSignal(Message)),chatWindow,SLOT(receiveMesSlot(Message)));
        chatWindow->show();
        chatWindow->setHisMessages(hislist);
        chatWindowList.push_back(chatWindow);
    }
}

//************************************************

/*接受客户端连接*/
void MainWindow::acceptClientSlot()
{
    clientConnection=server->nextPendingConnection();
    connect(clientConnection,SIGNAL(readyRead()),this,SLOT(readClientSlot()));
}
/*读取客户端消息*/
void MainWindow::readClientSlot()
{
    QString mes=clientConnection->readAll();
    QString time=QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm::ss");
    QString nameTo=clientConnection->peerAddress().toString();
    nameTo=nameTo.mid(nameTo.indexOf("::ffff:")+7,-1);
    //设置来消息提醒
    for(int i=0;i<ui->listWidgetFriends->count();i++)
    {
        if(nameTo==ui->listWidgetFriends->item(i)->text())
        {
            //ui->listWidgetFriends->item(i)->setBackgroundColor(QColor(255,0,0));
            ui->listWidgetFriends->item(i)->setIcon(QIcon("./mes.ico"));
            ui->listWidgetFriends->item(i)->setBackgroundColor(QColor(255,0,0));
        }
    }

    Message message;
    message.mes=mes;
    message.name=nameTo;
    message.time=time;
    MessageList.push_back(message);

    emit sendMesSignal(message);

}
