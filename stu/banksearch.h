#ifndef BANKSEARCH_H
#define BANKSEARCH_H

#include <QWidget>
#include <QDateTime>
#include "myclient.h"

namespace Ui {
class BankSearch;
}

class BankSearch : public QWidget
{
    Q_OBJECT

public:
    explicit BankSearch(MyClient *client, QWidget *parent = nullptr);
    ~BankSearch();

private slots:
    void on_exitButton_clicked();

    void toWriteDown(const QString &mon);

signals:
    void searchHadExit();
    void writeDowmMoney(const QString &mon);

private:
    Ui::BankSearch *ui;
    MyClient *m_client;
};

#endif // BANKSEARCH_H
