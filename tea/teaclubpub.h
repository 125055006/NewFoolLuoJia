#ifndef TEACLUBPUB_H
#define TEACLUBPUB_H

#include <QWidget>
#include <QMap>
#include <QMessageBox>
#include <QLineEdit>
#include "myserver.h"

namespace Ui {
class TeaClubPub;
}

class TeaClubPub : public QWidget
{
    Q_OBJECT

public:
    explicit TeaClubPub(MyServer *server, QWidget *parent = nullptr);
    ~TeaClubPub();

private slots:
    void on_exitButton_clicked();
    void toPublish();

signals:
    void pubHadExit();
    void sendClubActi(const QString &acti_Info);
    void needCommit(const QString &Info);

private:
    Ui::TeaClubPub *ui;
    MyServer *m_server;
    QMap<QPushButton*, QLineEdit*> to_connect;   //依然是建立映射，但这里逻辑上key:QPusbButton value:QLineEdit
};

#endif // TEACLUBPUB_H
