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
        int colonIndex = message.indexOf(":");
        if (colonIndex == -1) {
            colonIndex = message.indexOf("："); // 中文冒号
        }

        if (colonIndex != -1) {
            QString StuInfo = message.mid(colonIndex + 1); // 跳过冒号
            qDebug() << "提取的学生信息：" << StuInfo;
            emit ReceiveStuInfo("学生信息:" + StuInfo);  // 重新加上前缀保持一致性
        } else {
            // 如果没有冒号，可能是旧格式
            QString StuInfo = message.mid(4);  // 去除前缀
            qDebug() << "旧格式学生信息：" << StuInfo;
            emit ReceiveStuInfo("学生信息:" + StuInfo);
        }
    }
    else if(message.startsWith("分数信息"))
    {
        QString temp="分数信息";
        QString ScoreInfo=message.mid(temp.length());
        emit ReturnScore(ScoreInfo);
    }
    else if(message=="收到")
    {
        emit ReturnAnswer();
    }
    /*if(message.startsWith("借书回复"))
    {
        QString temp="借书回复";
        QString ans=message.mid(temp.length());
        emit SendBookAns(ans);
    }*/
    else if(message.startsWith("书籍信息"))
    {
        QString temp="书籍信息";
        QString Book_Info=message.mid(temp.length());
        emit SendBookInfo(Book_Info);
    }
    else if(message.startsWith("社团活动记录"))
    {
        QString temp = "社团活动记录";
        QString Club_Info = message.mid(temp.length());
        emit SendClubInfo(Club_Info);
    }
    else if(message.startsWith("社团活动"))
    {
        QString temp = "社团活动";
        QString join_Info = message.mid(temp.length());
        emit SendJoinInfo(join_Info);
    }
    else if(message.startsWith("宿舍分配")) {
        QString temp = "宿舍分配";
        QString distri_Info = message.mid(temp.length());
        emit sendDistriInfo(distri_Info);
    }
    else if(message.startsWith("报修时间")) {
        QString temp = "报修时间";
        QString fixTime_Info = message.mid(temp.length());
        emit getFixTime(fixTime_Info);
    }
    else if(message.startsWith("学宿费发布")) {
        QString temp = "学宿费发布";
        QString fee_Info = message.mid(temp.length());
        emit getFeeInfo(fee_Info);
    }
    else if(message.startsWith("水电重置")) {
        emit getReInfo();
    }

    if(message.startsWith("电影信息"))
    {
        QString temp="电影信息";
        QString Movie_Info=message.mid(temp.length());
        emit SendMovieInfo(Movie_Info);
    }
}

void MyClient::onErrorOccurred(QAbstractSocket::SocketError error)   //异常处理
{
    Q_UNUSED(error);  // 明确告诉编译器这个参数是故意不使用的
    qDebug() << "连接错误:" << socket->errorString();
}

void MyClient::requestStudentInfo(const QString &studentId)
{

    qDebug() << "=== 客户端：开始请求学生信息 ===";
    qDebug() << "学号：" << studentId;
    qDebug() << "Socket 状态：" << socket->state();
    qDebug() << "是否连接：" << (socket->state() == QAbstractSocket::ConnectedState);

    if (!socket || socket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "客户端未连接，无法请求学生信息";
        return;
    }

    // 构造请求消息，格式为：REQUEST_STUDENT_INFO:学号
    QString message = "REQUEST_STUDENT_INFO:" + studentId;
    qDebug() << "发送的消息：" << message;

    // 发送请求到服务器
    socket->write(message.toUtf8());
    socket->flush();

    qDebug() << "已向服务器发送学生信息请求：" << studentId;
}
