#ifndef STUDORM_H
#define STUDORM_H

#include <QWidget>
#include "myclient.h"
#include "dormexchange.h"
#include "dormfix.h"

namespace Ui {
class StuDorm;
}

class StuDorm : public QWidget
{
    Q_OBJECT

public:
    explicit StuDorm(MyClient *client, QWidget *parent = nullptr);
    ~StuDorm();

private slots:
    void on_exitButton_clicked();

    void on_dormExchangeButton_clicked();

    void on_fixButton_clicked();

    void onReciveDorm(const QString &Info);

    void fixTimeGet(const QString &Info);

signals:
    void dormHadExit();

private:
    Ui::StuDorm *ui;
    MyClient *m_client;
    DormExchange *exchange;
    DormFix *fix;
};

#endif // STUDORM_H
