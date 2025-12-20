#ifndef TEACLUB_H
#define TEACLUB_H

#include <QWidget>
#include "myserver.h"
#include "teaclubpub.h"
#include "teaclubcomi.h"

namespace Ui {
class TeaClub;
}

class TeaClub : public QWidget
{
    Q_OBJECT

public:
    explicit TeaClub(MyServer *server, QWidget *parent = nullptr);
    ~TeaClub();

private slots:
    void on_exitButton_clicked();

    void on_publishButton_clicked();

    void on_commitButton_clicked();

private:
    Ui::TeaClub *ui;
    MyServer *m_server;
    TeaClubPub *pub;
    TeaClubComi *comi;
};

#endif // TEACLUB_H
