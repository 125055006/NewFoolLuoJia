#ifndef CAMPUSLIFE_H
#define CAMPUSLIFE_H

#include <QWidget>
#include "myserver.h"
#include "teadorm.h"
#include "teabank.h"

namespace Ui {
class CampusLife;
}

class CampusLife : public QWidget
{
    Q_OBJECT

public:
    explicit CampusLife(MyServer *server, QWidget *parent = nullptr);
    ~CampusLife();

private slots:
    void on_dormButton_clicked();

    void on_exitButton_clicked();

    void on_bankButton_clicked();

signals:
    void campusHadExit();
    void sendToDorm(const QString &name);

private:
    Ui::CampusLife *ui;
    MyServer *m_server;
    TeaDorm *dorm;
    TeaBank *bank;
};

#endif // CAMPUSLIFE_H
