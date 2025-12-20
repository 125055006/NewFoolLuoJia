#ifndef DORMDISTRIBUTE_H
#define DORMDISTRIBUTE_H

#include <QWidget>
#include <QMessageBox>
#include "myserver.h"

namespace Ui {
class DormDistribute;
}

class DormDistribute : public QWidget
{
    Q_OBJECT

public:
    explicit DormDistribute(MyServer *server, QWidget *parent = nullptr);
    ~DormDistribute();

private slots:
    void on_exitButton_clicked();
    void onNameGet(const QString &name);
    void reciveExchange(const QString &Info);
    void on_commitButton_clicked();

    void on_rufuseButton_clicked();

signals:
    void getName(const QString &name);
    void distriHadExit();

private:
    Ui::DormDistribute *ui;
    MyServer *m_server;
};

#endif // DORMDISTRIBUTE_H
