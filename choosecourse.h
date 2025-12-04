#ifndef CHOOSECOURSE_H
#define CHOOSECOURSE_H

#include <QWidget>
#include<QList>
#include<QByteArray>
#include"myclient.h"
#include<QMessageBox>
namespace Ui {
class ChooseCourse;
}

class ChooseCourse : public QWidget
{
    Q_OBJECT

public:
    QList<QString> courses;
    explicit ChooseCourse(MyClient *client=nullptr,QWidget *parent = nullptr);
    ~ChooseCourse();

private slots:
    void on_Return_clicked();

    void on_c_gaoshu_clicked();

    void on_c_English_clicked();

    void on_c_gaocheng_clicked();

    void on_c_wuli_clicked();

    void on_d_gaoshu_clicked();

    void on_d_English_clicked();

    void on_d_gaocheng_clicked();

    void on_d_wuli_clicked();

    void on_confirm_clicked();
signals:
    void SendToCon(const QString &courses);
private:
    Ui::ChooseCourse *ui;
    QString TotalCourse;
    MyClient *m_client;
    int Course_num;
};

#endif // CHOOSECOURSE_H
