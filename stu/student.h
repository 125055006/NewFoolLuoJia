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

    void setStudentId(const QString &id);

    void loadStudentInfoFromLocal();

private slots:
    void on_Return_clicked();

    void onReceiveStuInfo(const QString &info);

    void on_EditStudent_clicked();

private:
    Ui::Student *ui;

    MyClient *m_client;

    QString currentStudentId;

};

#endif // STUDENT_H
