#ifndef CONSULTSCORE_H
#define CONSULTSCORE_H

#include <QWidget>
#include"myclient.h"

class ChooseCourse;          //前向声明，避免重复包含
namespace Ui {
class ConsultScore;
}

class ConsultScore : public QWidget
{
    Q_OBJECT

public:
    void setChooseCourse(ChooseCourse *choosecourse);   //新增设置方法
    explicit ConsultScore(MyClient *client=nullptr,QWidget *parent = nullptr);
    ~ConsultScore();
private slots:
    void InputCourse(const QString &courses);
    void ShowScore(const QString &score);
    void on_Return_clicked();

private:
    Ui::ConsultScore *ui;
    MyClient *m_client;
    ChooseCourse *CourseInfo;   //通过setter方法初始化
};

#endif // CONSULTSCORE_H
