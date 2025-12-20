#ifndef BANKEXPENSE_H
#define BANKEXPENSE_H

#include <QWidget>
#include "myclient.h"

namespace Ui {
class BankExpense;
}

class BankExpense : public QWidget
{
    Q_OBJECT

public:
    explicit BankExpense(MyClient *client, int mon, QWidget *parent = nullptr);
    ~BankExpense();

private slots:
    void on_exitButton_clicked();

    void on_commitButton_clicked();

signals:
    void expenseHadExit();
    void monChanged(const QString &mon); //这个是接收外界信息的
    void sendMoneyInfo(const QString &mon); //这个是向外界发送信息的

private:
    Ui::BankExpense *ui;
    MyClient *m_client;
    bool isThisMonth;
    bool isThisYear;
    int money;
};

#endif // BANKEXPENSE_H
