#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(QString name) :
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    nameTo=name;
    this->setWindowTitle(QString::fromLocal8Bit("正在与%1聊天...").arg(nameTo));
    this->setWindowIcon(QIcon("./mes.ico"));
    ui->lineEditMes->setFocus();
    ui->textEditShow->setFocusPolicy(Qt::NoFocus);

    //链接
    connect(ui->pushButtonSend,SIGNAL(clicked(bool)),this,SLOT(sendMesSlot()));//发送消息
    connect(ui->lineEditMes,SIGNAL(returnPressed()),this,SLOT(sendMesSlot()));

    connect(ui->textEditShow,SIGNAL(textChanged()),this,SLOT(roolToEndSlot())); //textEdit滚动到最下面

    connect(ui->pushButtonClear,SIGNAL(clicked(bool)),this,SLOT(clearHisSlot())); //清空记录
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

/*设置历史消息*/
void ChatWindow::setHisMessages(QList<Message> hislist)
{
    for(int i=0;i<hislist.count();i++)
    {
        ui->textEditShow->append(hislist.at(i).time+"--"+hislist.at(i).name+":");
        ui->textEditShow->append(hislist.at(i).mes);
    }
}

//*************************************************************slots


/*发送消息*/
void ChatWindow::sendMesSlot()
{
    QString mes=ui->lineEditMes->text();
    if(mes.isEmpty()) return ;

    int ret=tcpTools.sendMsg(nameTo,mes);
    if(ret)
    {
        QString time=QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm::ss");
        ui->textEditShow->append(time+"--Me:");
        ui->textEditShow->append(mes);
    }
    ui->lineEditMes->clear();
    ui->lineEditMes->setFocus();
}
/*清空聊天记录*/
void ChatWindow::clearHisSlot()
{
    ui->textEditShow->clear();
}

/*滚动到最下面*/
void ChatWindow::roolToEndSlot()
{
    ui->textEditShow->verticalScrollBar()->setSliderPosition(ui->textEditShow->verticalScrollBar()->maximum());
}

/*接受消息*/
void ChatWindow::receiveMesSlot(Message mes)
{
    if(mes.name==nameTo)
    {
        ui->textEditShow->append(mes.time+"--"+mes.name+":");
        ui->textEditShow->append(mes.mes);
    }
}
