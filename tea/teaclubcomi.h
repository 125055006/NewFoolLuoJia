#ifndef TEACLUBCOMI_H
#define TEACLUBCOMI_H

#include <QWidget>
#include <QLineEdit>
#include <QMap>
#include <QMessageBox>
#include "myserver.h"

namespace Ui {
class TeaClubComi;
}

class TeaClubComi : public QWidget
{
    Q_OBJECT

public:
    explicit TeaClubComi(MyServer *server, QWidget *parent = nullptr);
    ~TeaClubComi();

private slots:
    void on_exitButton_clicked();
    void newActi(const QString &Info);
    void finishActi();
    void isJoin();

signals:
    void comiHadExit();
    void toDoNew(const QString& Info);

private:
    Ui::TeaClubComi *ui;
    MyServer *m_server;
    QMap<QLineEdit*, QPushButton*> to_connect; //依旧建立映射关系
    int count;
    bool join;
};

#endif // TEACLUBCOMI_H
