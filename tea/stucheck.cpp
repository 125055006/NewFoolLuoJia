#include "stucheck.h"
#include "ui_stucheck.h"

StuCheck::StuCheck(Record *re_cord,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StuCheck)
    ,re_cord(re_cord)
{
    ui->setupUi(this);
    connect(re_cord,&Record::sendStuInfo,this,&StuCheck::SaveInfo);
    ui->remove->hide();
}

StuCheck::~StuCheck()
{
    delete ui;
}

void StuCheck::on_Return_clicked()
{
    this->close();
    ui->nameLable->clear();
    ui->sexLable->clear();
    ui->ageLable->clear();
    ui->majorLable->clear();
    ui->classLable->clear();
    ui->phoneLable->clear();
    ui->addressLable->clear();
    ui->le_id_check->clear();
    ui->remove->hide();
}

void StuCheck::SaveInfo(const QString &info)
{
    qDebug()<<"收到信息"<<info;
    students.append(info);
    qDebug()<<info<<"已录入"<<"目前共有"<<students.size()<<"条学生信息";
}

void StuCheck::on_Check_clicked()
{
    object=0;
    Found=false;
    if(students.size()==0)
    {
        QMessageBox::warning(this,"提示","目前未记录学生");
    }
    QString target=ui->le_id_check->text();
    for(int i=0;i<students.size();i++)
    {
        QStringList part=students[i].split('/');
        if(part[0]==target)
        {
            Found=true;
            ui->nameLable->setText("姓名："+part[1]);
            ui->sexLable->setText("性别："+part[2]);
            ui->ageLable->setText("年龄："+part[3]);
            ui->majorLable->setText("专业："+part[4]);
            ui->classLable->setText("班级："+part[5]);
            ui->phoneLable->setText("联系方式："+part[6]);
            ui->addressLable->setText("家庭地址："+part[7]);
            object=i;
            ui->remove->show();
        }
        if(i==students.size()-1&&!Found)
        {
            QMessageBox::warning(this,"提示","未找到该学生");
        }
    }
}


void StuCheck::on_remove_clicked()
{
    students.remove(object);
    QMessageBox::warning(this,"提示","删除成功");
}

