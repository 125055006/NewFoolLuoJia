#ifndef BUS_H
#define BUS_H

#include <QWidget>
#include"myclient.h"
namespace Ui {
class Bus;
}

class Bus : public QWidget
{
    Q_OBJECT

public:
    explicit Bus(MyClient *client=nullptr,QWidget *parent = nullptr);
    ~Bus();

private slots:
    void on_Return_clicked();

    void on_bus1_clicked();

    void on_bus2_clicked();

    void on_bus3_clicked();

private:
    Ui::Bus *ui;
    MyClient *m_client;
};

#endif // BUS_H
