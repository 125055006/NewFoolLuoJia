#ifndef STUACTIJOIN_H
#define STUACTIJOIN_H

#include <QWidget>
#include <QMap>
#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>
#include "myclient.h"

namespace Ui {
class StuActiJoin;
}

class StuActiJoin : public QWidget
{
    Q_OBJECT

public:
    explicit StuActiJoin(MyClient *client, QWidget *parent = nullptr);
    ~StuActiJoin();

signals:
    void joinExit();
    void hasJoined();

private slots:
    void on_exitButton_clicked();
    void newJoin(const QString &join_Info);
    void toJoinActi();

private:
    Ui::StuActiJoin *ui;
    MyClient *m_client;
    QMap<QLineEdit*, QPushButton*> to_connect_two;  //建立LineEdit和PushButton的映射关系
    int count;
};

#endif // STUACTIJOIN_H
