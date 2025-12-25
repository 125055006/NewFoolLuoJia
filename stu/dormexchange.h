#ifndef DORMEXCHANGE_H
#define DORMEXCHANGE_H

#include <QWidget>
#include <QMessageBox>
#include "myclient.h"

namespace Ui {
class DormExchange;
}

class DormExchange : public QWidget
{
    Q_OBJECT

public:
    explicit DormExchange(MyClient *client, QWidget *parent = nullptr);
    ~DormExchange();

private slots:
    void on_exitButton_clicked();
    void onOtherOptionChosed();

    void on_commitBotton_clicked();

signals:
    void exchangeHadExit();

private:
    Ui::DormExchange *ui;
    MyClient *m_client;
};

#endif // DORMEXCHANGE_H
