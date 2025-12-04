#include "myclient.h"

MyClient::MyClient(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, &MyClient::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &MyClient::onReadyRead);
    connect(socket, &QAbstractSocket::errorOccurred, this, &MyClient::onErrorOccurred);
}

void MyClient::connectToServer(const QString &host, quint16 port)    //建立连接
{
    qDebug() << "尝试连接到服务器:" << host << ":" << port;
    socket->connectToHost(host, port);
}

void MyClient::sendMessage(const QString &message)
{
    if (socket->state() == QAbstractSocket::ConnectedState)    //连接状态检测
    {
        socket->write(message.toUtf8());
    } else {
        qDebug() << "未连接到服务器，无法发送消息";
    }
}

void MyClient::onConnected()
{
    qDebug() << "连接成功";
    sendMessage("Hello World");
}

void MyClient::onReadyRead()
{
    QByteArray data = socket->readAll();
    QString message = QString::fromUtf8(data);
    qDebug() << "收到消息:" << message;
    if(message.startsWith("学生信息"))       //通过前缀检查信息类型
    {
        QString StuInfo=message.mid(4);      //去除前缀
        emit ReceiveStuInfo(StuInfo);
    }
    if(message.startsWith("分数信息"))
    {
        QString temp="分数信息";
        QString ScoreInfo=message.mid(temp.length());
        emit ReturnScore(ScoreInfo);
    }
    if(message=="收到")
    {
        emit ReturnAnswer();
    }
    /*if(message.startsWith("借书回复"))
    {
        QString temp="借书回复";
        QString ans=message.mid(temp.length());
        emit SendBookAns(ans);
    }*/
    if(message.startsWith("书籍信息"))
    {
        QString temp="书籍信息";
        QString Book_Info=message.mid(temp.length());
        emit SendBookInfo(Book_Info);
    }
}

void MyClient::onErrorOccurred(QAbstractSocket::SocketError error)   //异常处理
{
    qDebug() << "连接错误:" << socket->errorString();
}
