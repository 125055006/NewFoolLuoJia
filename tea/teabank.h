#ifndef TEABANK_H
#define TEABANK_H

#include <QWidget>
#include <QMessageBox>
#include "myserver.h"

namespace Ui {
class TeaBank;
}

class TeaBank : public QWidget
{
    Q_OBJECT

public:
    explicit TeaBank(MyServer *server, QWidget *parent = nullptr);
    ~TeaBank();

private slots:
    void on_exitButton_clicked();

    void on_commitButton_clicked();

    void on_reButton_clicked();

signals:
    void bankHadExit();

private:
    Ui::TeaBank *ui;
    MyServer *m_server;
};

#endif // TEABANK_H
