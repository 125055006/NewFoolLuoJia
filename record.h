#ifndef RECORD_H
#define RECORD_H

#include <QWidget>
#include"myserver.h"
#include<QMessageBox>
#include<QList>
namespace Ui {
class Record;
}

class Record : public QWidget
{
    Q_OBJECT

public:
    QList<QString> idHouse;
    explicit Record(MyServer *server=nullptr,QWidget *parent = nullptr);
    ~Record();

private slots:
    void on_Save_clicked();
    //void onGetStuInfo(const QString &info);
    void on_Cancel_clicked();

signals:
    void sendStuInfo(const QString &info);
private:
    bool isRepeated;
    Ui::Record *ui;
    MyServer *server;
};

#endif // RECORD_H
