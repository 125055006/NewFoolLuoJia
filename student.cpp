#include "student.h"
#include "ui_student.h"

Student::Student(MyClient *client,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Student)
    ,m_client(client)
{
    ui->setupUi(this);
    if(m_client)     //连接信号到槽函数
    {
        connect(m_client,&MyClient::ReceiveStuInfo,this,&Student::onReceiveStuInfo);
    }
}

Student::~Student()
{
    delete ui;
}

void Student::on_Return_clicked()
{
    this->close();
}

void Student::onReceiveStuInfo(const QString &info)
{
    qDebug()<<"收到信息："<<info;
    QStringList part=info.split('/');
    {
        ui->idEdit->setText(part[0]);
        ui->nameEdit->setText(part[1]);
        ui->sexEdit->setText(part[2]);
        ui->ageEdit->setText(part[3]);
        ui->majorEdit->setText(part[4]);
        ui->classEdit->setText(part[5]);
        ui->phoneEdit->setText(part[6]);
        ui->addressEdit->setText(part[7]);
    }
}
