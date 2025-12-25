#ifndef RECORD_H
#define RECORD_H

#include "studentmanager.h"
#include"myserver.h"

#include <QWidget>
#include<QMessageBox>
#include<QList>

namespace Ui {
class Record;
}

class Record : public QWidget
{
    Q_OBJECT

public:
    explicit Record(MyServer *server=nullptr,QWidget *parent = nullptr);
    ~Record();

private slots:
    void on_Save_clicked();
    void on_Cancel_clicked();

signals:
    void sendStuInfo(const QString &info);

private:
    void setupConnections();
    void clearAllInputs();

    Ui::Record *ui;
    MyServer *server;
};

#endif // RECORD_H
