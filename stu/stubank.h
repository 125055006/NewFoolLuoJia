#ifndef STUBANK_H
#define STUBANK_H

#include <QWidget>
#include "bankkr.h"
#include "myclient.h"
#include "banksearch.h"
#include "bankexpense.h"

namespace Ui {
class StuBank;
}

class StuBank : public QWidget
{
    Q_OBJECT

public:
    explicit StuBank(MyClient *client, QWidget *parent = nullptr);
    ~StuBank();

private slots:
    void on_exitButton_clicked();

    void on_krButton_clicked();

    void reciveMoney(const QString &mon);

    void on_searchButton_clicked();

    void on_lostButton_clicked();

    void on_consumeButton_clicked();

signals:
    void bankHadExit();
    void giveOutMoney(const QString &mon);
    void expenseChanged(const QString &mon);

private:
    Ui::StuBank *ui;
    BankKr *kr;
    MyClient *m_client;
    BankSearch *search;
    int money;
    BankExpense *expense;
    bool lost;
};

#endif // STUBANK_H
