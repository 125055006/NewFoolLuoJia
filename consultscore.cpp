#include "consultscore.h"
#include "ui_consultscore.h"
#include"choosecourse.h"

ConsultScore::ConsultScore(MyClient *client,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConsultScore)
    ,m_client(client),
    CourseInfo(nullptr)
{
    ui->setupUi(this);
    connect(m_client,&MyClient::ReturnScore,this,&ConsultScore::ShowScore);
}
ConsultScore::~ConsultScore()
{
    delete ui;
}
void ConsultScore::setChooseCourse(ChooseCourse *chooseCourse)
{
    CourseInfo=chooseCourse;
    if(CourseInfo)
    {
        connect(CourseInfo,&ChooseCourse::SendToCon,this,&ConsultScore::InputCourse);
    }
}
void ConsultScore::InputCourse(const QString &courses)
{
    QStringList part=courses.split('/');

    for(int i=0;i<part.size();i++)
    {
        /*QString EditName="course"+QString::number(i+1);
        QLineEdit *edit=this->findChild<QLineEdit*>(EditName);     //动态命名窗口

        if(edit)
        {
            edit->setText(part[i]);
        }
        else
        {
            QMessageBox::warning(this,"错误","未获取到课程信息");
        }*/
        switch(i+1)
        {
        case 1:
            ui->course1->setText(part[0]);
            break;
        case 2:
            ui->course2->setText(part[1]);
            break;
        case 3:
            ui->course3->setText(part[2]);
            break;
        case 4:
            ui->course4->setText(part[3]);
            break;
        }
    }
}

void ConsultScore::ShowScore(const QString &score)
{
    QStringList part=score.split('/');
    for(int i=0;i<part.size();i++)
    {
        /*QString EditName="score"+QString::number(i+1);
        QLineEdit *edit=this->findChild<QLineEdit*>(EditName);     //动态命名窗口

        if(edit)
        {
            edit->setText(part[i]);
        }
        else
        {
            QMessageBox::warning(this,"错误","未获取到分数信息");
        }*/
        switch(i+1)
        {
        case 1:
            ui->score1->setText(part[0]);
            break;
        case 2:
            ui->score2->setText(part[1]);
            break;
        case 3:
            ui->score3->setText(part[2]);
            break;
        case 4:
            ui->score4->setText(part[3]);
            break;
        }
    }
}
void ConsultScore::on_Return_clicked()
{
    this->close();
}

