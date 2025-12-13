#ifndef ANSWER_MTH_H
#define ANSWER_MTH_H

#include <QWidget>
#include"myserver.h"
namespace Ui {
class Answer_MTH;
}

class Answer_MTH : public QWidget
{
    Q_OBJECT

public:
    explicit Answer_MTH(MyServer *server=nullptr,QWidget *parent = nullptr);
    ~Answer_MTH();
private slots:
    void ShowMTH(const QString &MTH_Info);
    void on_Return_clicked();

private:
    Ui::Answer_MTH *ui;
    MyServer *m_server;
};

#endif // ANSWER_MTH_H
