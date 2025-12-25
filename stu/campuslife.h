#ifndef CAMPUSLIFE_H
#define CAMPUSLIFE_H

#include <QWidget>
#include <myclient.h>
#include <studorm.h>
#include "stubank.h"

namespace Ui {
class CampusLife;
}

class CampusLife : public QWidget
{
    Q_OBJECT

public:
    explicit CampusLife(MyClient *client, QWidget *parent = nullptr);
    ~CampusLife();

private slots:
    void on_dormButton_clicked();

    void on_exitButton_clicked();

    void on_eCardButton_clicked();

signals:
    void campusHadExit();

private:
    Ui::CampusLife *ui;
    MyClient *m_client;
    StuDorm *dorm;
    StuBank *bank;
};

#endif // CAMPUSLIFE_H
