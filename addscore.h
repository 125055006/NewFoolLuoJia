#ifndef ADDSCORE_H
#define ADDSCORE_H

#include <QWidget>
#include<QLineEdit>
#include<QMessageBox>
#include<QDebug>
#include"myserver.h"
namespace Ui {
class AddScore;
}

class AddScore : public QWidget
{
    Q_OBJECT

public:
    explicit AddScore(MyServer *server=nullptr,QWidget *parent = nullptr);
    ~AddScore();

private:
    Ui::AddScore *ui;
    QString TotalScore;
    MyServer *m_server;
private slots:
    //void GiveScore();
    void AddCourses(const QString &courses);
    void on_Return_clicked();
    void on_Confirm_clicked();
};

#endif // ADDSCORE_H
