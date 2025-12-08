#ifndef ADDBOOKS_H
#define ADDBOOKS_H

#include <QWidget>
#include<QMessageBox>
#include<myserver.h>

struct book
{
    QString name;
    QString introduce;
    bool isBorrowed;
};
namespace Ui {
class AddBooks;
}

class AddBooks : public QWidget
{
    Q_OBJECT

public:
    QList<book> books;
    explicit AddBooks(MyServer *server,QWidget *parent = nullptr);
    ~AddBooks();
signals:
    void SendToLib(QList<book> &books);
private slots:
    void on_Return_clicked();

    void on_add_clicked();

private:
    Ui::AddBooks *ui;
    MyServer *m_server;
};

#endif // ADDBOOKS_H
