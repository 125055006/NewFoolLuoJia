#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QDebug>

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

private:
    QTcpServer *server;
    QList<QTcpSocket*> clients;
};

#endif // MYSERVER_H
