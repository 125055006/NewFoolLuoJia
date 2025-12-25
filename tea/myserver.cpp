#include "myserver.h"
#include "studentmanager.h"

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
    QString message = QString::fromUtf8(data).trimmed();  // 添加 trim()
    qDebug() << "收到客户端消息:" << message << "来自:" << clientSocket->peerAddress().toString();

    // 首先判断是否是学生信息请求
    if (message.startsWith("REQUEST_STUDENT_INFO:")) {
        // 处理学生信息请求
        handleClientRequest(clientSocket, message);
        return;  // 处理完直接返回，不进行后续广播
    }

    // 原有逻辑：广播消息
    sendToAllClients(clientSocket->peerAddress().toString() + " : " + message);

    if(message.startsWith("课程信息："))
    {
        QString temp="课程信息：";
        QString courses=message.mid(temp.length());      //去掉开头的识别信息,防止因中文可能占用多个字节出错
        emit SendCourses(courses);
    }
    else if(message.startsWith("教评信息"))
    {
        QString temp="教评信息";
        QString com_Info=message.mid(temp.length());
        qDebug()<<"已收到教评信息";
        emit SendCom_Info(com_Info);
    }
    else if(message.startsWith("心预信息"))
    {
        QString temp="心预信息";
        QString MTH_Info=message.mid(temp.length());
        qDebug()<<"收到心理咨询预约信息";
        emit SendMTH(MTH_Info);
    }
    else if(message.startsWith("学生信息:"))
    {
        // 处理教师端发送的学生信息
        // 这里可以添加处理逻辑，比如记录日志等
        qDebug() << "收到学生信息更新：" << message;
        // 广播给学生端
        sendToAllClients(message);
    }
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

// 处理客户端请求
void MyServer::handleClientRequest(QTcpSocket *clientSocket, const QString &request)
{
    if (request.startsWith("REQUEST_STUDENT_INFO:")) {
        QString studentId = request.mid(21); // 去掉 "REQUEST_STUDENT_INFO:" 前缀
        handleStudentInfoRequest(studentId, clientSocket);
    }
}

// 处理学生信息请求
void MyServer::handleStudentInfoRequest(const QString &studentId, QTcpSocket *clientSocket)
{
    qDebug() << "处理学生信息请求，学号：" << studentId;

    // 从本地管理器中获取学生信息
    StudentInfo info = StudentManager::instance().getStudentById(studentId);

    if (!info.id.isEmpty()) {
        // 找到学生信息，发送给学生端
        QString response = "学生信息:" + info.toString();
        clientSocket->write(response.toUtf8());
        clientSocket->flush();

        qDebug() << "已发送学生信息给学生端：" << studentId;
    } else {
        // 没有找到学生信息
        QString response = "ERROR:学生信息不存在:" + studentId;
        clientSocket->write(response.toUtf8());
        clientSocket->flush();

        qDebug() << "学生信息不存在：" << studentId;
    }
}
