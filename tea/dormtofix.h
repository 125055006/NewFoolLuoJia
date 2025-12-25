#ifndef DORMTOFIX_H
#define DORMTOFIX_H

#include <QWidget>
#include <QMessageBox>
#include "myserver.h"

namespace Ui {
class DormToFix;
}

class DormToFix : public QWidget
{
    Q_OBJECT

public:
    explicit DormToFix(MyServer *server, QWidget *parent = nullptr);
    ~DormToFix();

private slots:
    void on_exitButton_clicked();
    void displayFixInfo(const QString &Info);

    void on_commitButton_clicked();

signals:
    void dormtofixHadExit();

private:
    Ui::DormToFix *ui;
    MyServer *m_server;
};

#endif // DORMTOFIX_H
