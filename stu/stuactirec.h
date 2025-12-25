#ifndef STUACTIREC_H
#define STUACTIREC_H

#include <QWidget>
#include "myclient.h"
#include <QDebug>

namespace Ui {
class StuActiRec;
}

class StuActiRec : public QWidget
{
    Q_OBJECT

public:
    explicit StuActiRec(MyClient *client, QWidget *parent = nullptr);
    ~StuActiRec();

private slots:
    void displayInfo(const QString &ClubInfo);

    void on_exitButton_clicked();

signals:
    void recExit();

private:
    Ui::StuActiRec *ui;
    MyClient *m_client;
    quint8 count;
};

#endif // STUACTIREC_H
