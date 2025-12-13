#ifndef MENTALHEAL_H
#define MENTALHEAL_H

using namespace std;

#include <QWidget>
#include<vector>
#include<QButtonGroup>
#include"myclient.h"
#include<QMessageBox>
namespace Ui {
class MentalHeal;
}

class MentalHeal : public QWidget
{
    Q_OBJECT

public:
    vector<QString> teas;
    explicit MentalHeal(MyClient *client=nullptr,QWidget *parent = nullptr);
    ~MentalHeal();

private slots:
    void on_Send_clicked();

    void on_Return_2_clicked();

private:
    Ui::MentalHeal *ui;
    MyClient *m_client;
};

#endif // MENTALHEAL_H
