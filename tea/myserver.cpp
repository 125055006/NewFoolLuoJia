#include "myserver.h"

MyServer::MyServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &MyServer::onNewConnection);
}

bool MyServer::startServer(quint16 port)
{
    if (!server->listen(QHostAddress::Any, port))       //监听客户端
    {
        qDebug() << "服务器启动失败:" << server->errorString();
        return false;
    }

    qDebug() << "服务器已启动，监听端口:" << port;
    return true;
}

void MyServer::onNewConnection()
{
    QTcpSocket *clientSocket = server->nextPendingConnection();  //获取连接请求
    clients.append(clientSocket);             //记录连接
    qDebug() << "新客户端连接:" << clientSocket->peerAddress().toString()
             << ":" << clientSocket->peerPort();    //记录IP地址和端口号
    qDebug() << "当前客户端数量:" << clients.size();
    connect(clientSocket, &QTcpSocket::readyRead, this, &MyServer::onClientReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &MyServer::onClientDisconnected);
    QString welcomeMsg = "welcome";
    clientSocket->write(welcomeMsg.toUtf8());
}

void MyServer::onClientReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());   //获取信号源指针
    if (!clientSocket) return;
    QByteArray data = clientSocket->readAll();  //获取数据
    QString message = QString::fromUtf8(data);
    qDebug() << "收到客户端消息:" << message << "来自:" << clientSocket->peerAddress().toString();
    sendToAllClients(clientSocket->peerAddress().toString() + " : " + message);
    if(message.startsWith("课程信息："))
    {
        QString temp="课程信息：";
        QString courses=message.mid(temp.length());      //去掉开头的识别信息,防止因中文可能占用多个字节出错
        emit SendCourses(courses);
    }
    if(message.startsWith("教评信息"))
    {
        QString temp="教评信息";
        QString com_Info=message.mid(temp.length());
        qDebug()<<"已收到教评信息";
        emit SendCom_Info(com_Info);
    }
    /*if(message.startsWith("借书目标"))
    {
        QString temp="借书目标";
        QString target=message.mid(temp.length());
        qDebug()<<"收到借书目标"<<target;
        emit SendTargetBook(target);
    }*/
}

void MyServer::onClientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;
    clients.removeOne(clientSocket);
    qDebug() << "断开连接:" << clientSocket->peerAddress().toString();
    qDebug() << "剩余客户端数量:" << clients.size();
    clientSocket->deleteLater();  //删除没用的指针
}

void MyServer::sendToAllClients(const QString &message)   //发信息
{
    QByteArray data = message.toUtf8();

    for (QTcpSocket *client : clients) {
        if (client->state() == QTcpSocket::ConnectedState) {
            qDebug()<<"服务器已发送";
            client->write(data);
        }
    }
}
