#ifndef TEADORM_H
#define TEADORM_H

#include <QWidget>
#include "myserver.h"
#include "dormdistribute.h"
#include "dormtofix.h"

namespace Ui {
class TeaDorm;
}

class TeaDorm : public QWidget
{
    Q_OBJECT

public:
    explicit TeaDorm(MyServer *server, QWidget *parent = nullptr);
    ~TeaDorm();

private slots:
    void on_exitButton_clicked();

    void on_distributeButton_clicked();

    void on_toFixButton_clicked();

signals:
    void dormHadExit();
    void sendToDistri(const QString &Info);

private:
    Ui::TeaDorm *ui;
    MyServer *m_server;
    DormDistribute *distri;
    DormToFix *tofix;
};

#endif // TEADORM_H
