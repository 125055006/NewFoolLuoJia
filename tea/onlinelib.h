#ifndef ONLINELIB_H
#define ONLINELIB_H

#include <QWidget>
#include"myserver.h"
#include"addbooks.h"
#include<QList>
#include<QDebug>


namespace Ui {
class OnlineLib;
}

class OnlineLib : public QWidget
{
    Q_OBJECT

public:

    explicit OnlineLib(MyServer *server,QWidget *parent = nullptr);
    ~OnlineLib();

private slots:
    void ShowBooks(QList<book> &books);

    void on_Return_clicked();

    void on_AddBooks_clicked();

    void on_find_clicked();

    void on_delete_2_clicked();

private:
    QString ans;
    Ui::OnlineLib *ui;
    MyServer *m_server;
    AddBooks *add_books;
};

#endif // ONLINELIB_H
