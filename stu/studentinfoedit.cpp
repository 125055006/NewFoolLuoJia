#include "studentinfoedit.h"
#include "ui_studentinfoedit.h"
#include <QMessageBox>
#include <QDebug>

StudentInfoEdit::StudentInfoEdit(const QString &studentId,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudentInfoEdit)
    , currentStudentId(studentId)
{
    ui->setupUi(this);

    setWindowTitle("编辑个人信息 - " + studentId);

    ui->ID->setReadOnly(true);

    ui->ID->setText(studentId);

    loadStudentInfo();

    connect(ui->saveButton, &QPushButton::clicked, this, &StudentInfoEdit::on_saveButton_clicked);

    connect(ui->cancelButton, &QPushButton::clicked, this, &StudentInfoEdit::on_cancelButton_clicked);

    connect(ui->returnButton, &QPushButton::clicked, this, &StudentInfoEdit::on_cancelButton_clicked);
}

StudentInfoEdit::~StudentInfoEdit()
{
    delete ui;
}

void StudentInfoEdit::loadStudentInfo()
{
    // 从管理器获取现有信息
    StudentInfo info = StudentManager::instance().getStudentById(currentStudentId);

    // 如果存在信息，加载到界面
    if (!info.id.isEmpty()) {
        ui->NAME->setText(info.name);
        ui->GENDER->setText(info.gender);
        ui->AGE->setText(info.age);
        ui->MAJORS->setText(info.major);
        ui->CLASS->setText(info.className);
        ui->PHNOENUM->setText(info.phone);
        ui->ADDRESS->setText(info.address);
    } else {
        // 如果没有信息，清空界面
        ui->NAME->clear();
        ui->GENDER->clear();
        ui->AGE->clear();
        ui->MAJORS->clear();
        ui->CLASS->clear();
        ui->PHNOENUM->clear();
        ui->ADDRESS->clear();
    }
}

void StudentInfoEdit::saveStudentInfo()
{
    // 验证输入
    if (ui->NAME->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "警告", "姓名不能为空！");
        ui->NAME->setFocus();
        return;
    }

    StudentInfo info;

    info.id = currentStudentId;

    info.name = ui->NAME->text().trimmed();

    info.gender = ui->GENDER->text().trimmed();

    info.age = ui->AGE->text().trimmed();

    info.major = ui->MAJORS->text().trimmed();

    info.className = ui->CLASS->text().trimmed();

    info.phone = ui->PHNOENUM->text().trimmed();

    info.address = ui->ADDRESS->text().trimmed();

    StudentManager::instance().addOrUpdateStudent(info);

    qDebug() << "学生信息已保存：" << info.toString();
}

void StudentInfoEdit::on_returnButton_clicked()
{

}


void StudentInfoEdit::on_cancelButton_clicked()
{
    // 询问是否保存
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认", "是否放弃编辑？",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 发射取消信号
        emit editCancelled();

        // 关闭窗口
        this->close();
    }
}


void StudentInfoEdit::on_saveButton_clicked()
{
    saveStudentInfo();
    QMessageBox::information(this, "成功", "个人信息已保存！");

    // 发射编辑完成信号
    emit editCompleted(currentStudentId);

    // 关闭窗口
    this->close();
}

