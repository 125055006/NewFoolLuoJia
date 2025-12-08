#ifndef STUDENT_H
#define STUDENT_H

#include <QWidget>
#include"myclient.h"
#include<QMessageBox>
namespace Ui {
class Student;
}

class Student : public QWidget
{
    Q_OBJECT

public:
    explicit Student(MyClient *client=nullptr,QWidget *parent = nullptr);
    ~Student();

private slots:
    void on_Return_clicked();
    void onReceiveStuInfo(const QString &info);

private:
    Ui::Student *ui;
    MyClient *m_client;
};

#endif // STUDENT_H
