#ifndef MYSERVER_H
#define MYSERVER_H

#include "studentmanager.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QDebug>
#include<QMessageBox>


class MyServer : public QObject
{
    Q_OBJECT

public:
    explicit MyServer(QObject *parent = nullptr);
    bool startServer(quint16 port);
    void sendToAllClients(const QString &message);

private slots:
    void onNewConnection();
    void onClientReadyRead();
    void onClientDisconnected();
    void handleClientRequest(QTcpSocket *clientSocket, const QString &request);
signals:
   // void GetStuInfo(const QString &info);
    void SendCourses(const QString &course);
    void SendCom_Info(const QString &com_Info);
    void SendMTH(const QString &MTH_Info);
    //void SendTargetBook(const QString &target);
private:
    QTcpServer *server;
    QList<QTcpSocket*> clients;
    void handleStudentInfoRequest(const QString &studentId, QTcpSocket *clientSocket);
};

#endif // MYSERVER_H
