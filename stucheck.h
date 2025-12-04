#ifndef STUCHECK_H
#define STUCHECK_H

#include <QWidget>
#include"record.h"
#include<QList>
namespace Ui {
class StuCheck;
}

class StuCheck : public QWidget
{
    Q_OBJECT

public:
    QList<QString> students;
    explicit StuCheck(Record *re_cord=nullptr,QWidget *parent = nullptr);
    ~StuCheck();

private slots:
    void on_Return_clicked();
    void SaveInfo(const QString &info);
    void on_Check_clicked();
    void on_remove_clicked();

private:
    int object;
    bool Found;
    Ui::StuCheck *ui;
    Record *re_cord;
};

#endif // STUCHECK_H
