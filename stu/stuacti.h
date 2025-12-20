#ifndef STUACTI_H
#define STUACTI_H

#include <QWidget>
#include "myclient.h"
#include "stuactirec.h"
#include "stuactijoin.h"

namespace Ui {
class StuActi;
}

class StuActi : public QWidget
{
    Q_OBJECT

public:
    explicit StuActi(MyClient* clinet, QWidget *parent = nullptr);
    ~StuActi();

private slots:
    void on_exitButton_clicked();

    void on_recordButton_clicked();

    void on_joinButton_clicked();

private:
    Ui::StuActi *ui;
    MyClient *m_client;
    StuActiRec *rec;
    StuActiJoin *join;
};

#endif // STUACTI_H
