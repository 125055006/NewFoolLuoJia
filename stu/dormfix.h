#ifndef DORMFIX_H
#define DORMFIX_H

#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include "myclient.h"

namespace Ui {
class DormFix;
}

class DormFix : public QWidget
{
    Q_OBJECT

public:
    explicit DormFix(MyClient *client, QWidget *parent = nullptr);
    ~DormFix();

private slots:
    void on_exitButton_clicked();

    void on_commitButton_clicked();

signals:
    void fixHadExit();

private:
    Ui::DormFix *ui;
    MyClient *m_client;
};

#endif // DORMFIX_H
