#include "choosecourse.h"
#include "ui_choosecourse.h"

ChooseCourse::ChooseCourse(MyClient *m_client,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChooseCourse)
    ,m_client(m_client)
{
    ui->setupUi(this);
    Course_num=0;
    ui->d_English->hide();
    ui->d_gaocheng->hide();
    ui->d_gaoshu->hide();
    ui->d_wuli->hide();
}

ChooseCourse::~ChooseCourse()
{
    delete ui;
}

void ChooseCourse::on_Return_clicked()
{
    this->close();
}


void ChooseCourse::on_c_gaoshu_clicked()
{
    courses.append("高等数学A");
    ui->c_gaoshu->hide();
    ui->d_gaoshu->show();
    Course_num+=1;
}


void ChooseCourse::on_c_English_clicked()
{
    courses.append("大学交际英语");
    ui->c_English->hide();
    ui->d_English->show();
    Course_num+=1;
}


void ChooseCourse::on_c_gaocheng_clicked()
{
    courses.append("高级语言程序设计A");
    ui->c_gaocheng->hide();
    ui->d_gaocheng->show();
    Course_num+=1;
}


void ChooseCourse::on_c_wuli_clicked()
{
    courses.append("大学物理");
    ui->c_wuli->hide();
    ui->d_wuli->show();
    Course_num+=1;
}


void ChooseCourse::on_d_gaoshu_clicked()
{
    for(int i=0;i<courses.size();i++)
    {
        if(courses[i]=="高等数学A")
        {
            courses.remove(i);
            ui->d_gaoshu->hide();
            ui->c_gaoshu->show();
            QMessageBox::warning(this,"提示","恭喜！取消成功");
        }
    }
}


void ChooseCourse::on_d_English_clicked()
{
    for(int i=0;i<courses.size();i++)
    {
        if(courses[i]=="大学交际英语")
        {
            courses.remove(i);
            ui->d_English->hide();
            ui->c_English->show();
            QMessageBox::warning(this,"提示","恭喜！取消成功");
        }
    }
}


void ChooseCourse::on_d_gaocheng_clicked()
{
    for(int i=0;i<courses.size();i++)
    {
        if(courses[i]=="高级语言程序设计A")
        {
            courses.remove(i);
            ui->d_gaocheng->hide();
            ui->c_gaocheng->show();
            QMessageBox::warning(this,"提示","恭喜！取消成功");
        }
    }
}


void ChooseCourse::on_d_wuli_clicked()
{
    for(int i=0;i<courses.size();i++)
    {
        if(courses[i]=="大学物理")
        {
            courses.remove(i);
            ui->c_wuli->show();
            ui->d_wuli->hide();
            QMessageBox::warning(this,"提示","恭喜！取消成功");
        }
    }
}


void ChooseCourse::on_confirm_clicked()
{
    for(int i=0;i<courses.size();i++)
    {
        TotalCourse+=courses[i];
        TotalCourse+='/';
    }
    m_client->sendMessage("课程信息："+TotalCourse);
    emit SendToCon(TotalCourse);
    QMessageBox::warning(this,"提示","保存成功");
}

