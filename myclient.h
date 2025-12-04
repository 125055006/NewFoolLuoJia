#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include<QMessageBox>
class MyClient : public QObject
{
    Q_OBJECT

public:
    explicit MyClient(QObject *parent = nullptr);
    void connectToServer(const QString &host, quint16 port);
    void sendMessage(const QString &message);

private slots:
    void onConnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError error);
signals:
    void ReceiveStuInfo(const QString &info);
    void ReturnScore(const QString &score);
    void ReturnAnswer();
    void SendBookInfo(const QString &Book_Info);
    //void SendBookAns(const QString &ans);
private:
    QTcpSocket *socket;
};

#endif // MYCLIENT_H
