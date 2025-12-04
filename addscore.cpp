#include "addscore.h"
#include "ui_addscore.h"

AddScore::AddScore(MyServer *server,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddScore)
    ,m_server(server)
{
    ui->setupUi(this);
     TotalScore="分数信息：";
    connect(m_server,&MyServer::SendCourses,this,&AddScore::AddCourses);
    //connect(m_server,&MyServer::SendCourses,this,&AddScore::GiveScore);
}

AddScore::~AddScore()
{
    delete ui;
}

void AddScore::AddCourses(const QString &courses)
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

/*void AddScore::GiveScore()
{

}*/

void AddScore::on_Return_clicked()
{
    ui->course1->clear();
    ui->course2->clear();
    ui->course3->clear();
    ui->course4->clear();
    this->close();
}


void AddScore::on_Confirm_clicked()
{
    TotalScore="分数信息";
    for(int i=0;i<4;i++)
    {
        switch (i+1)
        {
        case 1:
            TotalScore+=ui->score1->text();
            TotalScore+='/';
            break;
        case 2:
            TotalScore+=ui->score2->text();
            TotalScore+='/';
            break;
        case 3:
            TotalScore+=ui->score3->text();
            TotalScore+='/';
            break;
        case 4:
            TotalScore+=ui->score4->text();
            TotalScore+='/';
            break;
        }
    }

    m_server->sendToAllClients(TotalScore);
    qDebug()<<"已发送分数："<<TotalScore;
    QMessageBox::warning(this,"提示","发送成功");
}

