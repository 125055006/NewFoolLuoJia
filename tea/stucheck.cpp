#include "stucheck.h"
#include "ui_stucheck.h"

StuCheck::StuCheck(Record *re_cord,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StuCheck)
    ,re_cord(re_cord)
    , studentManager(StudentManager::instance())
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

    StudentInfo student = StudentInfo::fromString(info);
    if (!student.id.isEmpty()) {
        studentManager.addOrUpdateStudent(student);
        qDebug() << "学生信息已保存到文件，学号：" << student.id;
    }
}

void StuCheck::on_Check_clicked()
{
    // 获取输入的学号
    QString targetId = ui->le_id_check->text().trimmed();

    if (targetId.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入学号");
        return;
    }

    // 从 StudentManager 查询学生信息
    StudentInfo student = studentManager.getStudentById(targetId);

    if (student.id.isEmpty()) {
        QMessageBox::warning(this, "提示", "未找到该学生");
        // 清空显示
        ui->nameLable->clear();
        ui->sexLable->clear();
        ui->ageLable->clear();
        ui->majorLable->clear();
        ui->classLable->clear();
        ui->phoneLable->clear();
        ui->addressLable->clear();
        ui->remove->hide();
        return;
    }

    // 显示学生信息
    ui->nameLable->setText("姓名：" + student.name);
    ui->sexLable->setText("性别：" + student.gender);
    ui->ageLable->setText("年龄：" + student.age);
    ui->majorLable->setText("专业：" + student.major);
    ui->classLable->setText("班级：" + student.className);
    ui->phoneLable->setText("联系方式：" + student.phone);
    ui->addressLable->setText("家庭地址：" + student.address);

    // 显示删除按钮
    ui->remove->show();
}

void StuCheck::on_remove_clicked()
{
    QString targetId = ui->le_id_check->text().trimmed();

    if (targetId.isEmpty()) {
        QMessageBox::warning(this, "提示", "没有要删除的学生");
        return;
    }

    // 从 StudentManager 删除学生
    studentManager.removeStudent(targetId);

    // 清空显示
    ui->nameLable->clear();
    ui->sexLable->clear();
    ui->ageLable->clear();
    ui->majorLable->clear();
    ui->classLable->clear();
    ui->phoneLable->clear();
    ui->addressLable->clear();
    ui->le_id_check->clear();
    ui->remove->hide();

    QMessageBox::information(this, "提示", "删除成功");
}

