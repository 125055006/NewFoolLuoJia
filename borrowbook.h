#ifndef BORROWBOOK_H
#define BORROWBOOK_H

#include <QWidget>
#include"myclient.h"
#include<QList>
#include<QDateTime>
struct book
{
    QString name;
    QString introduce;
    bool isBorrowed;
};
struct bor_book
{
    QString name;
    QDateTime bor_time;
};

namespace Ui {
class BorrowBook;
}

class BorrowBook : public QWidget
{
    Q_OBJECT

public:
    QList<book> books;
    QList<bor_book> bor_books;
    explicit BorrowBook(MyClient *client,QWidget *parent = nullptr);
    ~BorrowBook();

private slots:
    void on_Return_clicked();

    void on_find_clicked();

    void UpdataBooks(const QString &Book_Info);
    //void Result(const QString &ans);

    void on_RTB1_clicked();

    void on_RTB2_clicked();

    void on_RTB3_clicked();

signals:

private:
    QString target;
    Ui::BorrowBook *ui;
    MyClient *m_client;
};

#endif // BORROWBOOK_H
