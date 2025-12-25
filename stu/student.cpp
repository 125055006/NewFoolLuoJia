#include "student.h"
#include "ui_student.h"
#include "studentinfoedit.h"  // 添加头文件
#include "studentmanager.h"     // 添加头文件
#include <QDebug>

Student::Student(MyClient *client,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Student)
    ,m_client(client)
{
    ui->setupUi(this);

    ui->ID->setReadOnly(true);

    ui->NAME->setReadOnly(true);

    ui->GENDER->setReadOnly(true);

    ui->AGE->setReadOnly(true);

    ui->MAJORS->setReadOnly(true);

    ui->CLASS->setReadOnly(true);

    ui->PHONENUM->setReadOnly(true);

    ui->ADDRESS->setReadOnly(true);

    QString readOnlyStyle = "QLineEdit:read-only { background-color: #f0f0f0; border: 1px solid #cccccc; }";

    ui->ID->setStyleSheet(readOnlyStyle);

    ui->NAME->setStyleSheet(readOnlyStyle);

    ui->GENDER->setStyleSheet(readOnlyStyle);

    ui->AGE->setStyleSheet(readOnlyStyle);

    ui->MAJORS->setStyleSheet(readOnlyStyle);

    ui->CLASS->setStyleSheet(readOnlyStyle);

    ui->PHONENUM->setStyleSheet(readOnlyStyle);

    ui->ADDRESS->setStyleSheet(readOnlyStyle);
    //改变字体样式

    if(m_client)     //连接信号到槽函数
    {
        connect(m_client,&MyClient::ReceiveStuInfo,this,&Student::onReceiveStuInfo);
    }
}

Student::~Student()
{
    delete ui;
}

void Student::setStudentId(const QString &id)
{
    // 在“学号：”后面的编辑框中显示学号
    currentStudentId = id;

    ui->ID->setText(id);

    setWindowTitle("个人中心 - " + id);

    loadStudentInfoFromLocal();
}

void Student::on_Return_clicked()
{
    this->close();
}

void Student::loadStudentInfoFromLocal()
{
    if (currentStudentId.isEmpty()) return;

    StudentInfo info = StudentManager::instance().getStudentById(currentStudentId);

    if (!info.id.isEmpty()) {
        // 从本地文件加载信息
        ui->NAME->setText(info.name);

        ui->GENDER->setText(info.gender);

        ui->AGE->setText(info.age);

        ui->MAJORS->setText(info.major);

        ui->CLASS->setText(info.className);

        ui->PHONENUM->setText(info.phone);

        ui->ADDRESS->setText(info.address);

    }
    else
    {
        // 本地没有记录，清空其他字段（只保留学号）
        ui->NAME->clear();

        ui->GENDER->clear();

        ui->AGE->clear();

        ui->MAJORS->clear();

        ui->CLASS->clear();

        ui->PHONENUM->clear();

        ui->ADDRESS->clear();
    }
}

void Student::onReceiveStuInfo(const QString &info)
{
    qDebug()<<"收到信息："<<info;

    if(!info.startsWith("学生信息:")) {
        qDebug() << "不是学生信息，忽略：" << info;
        return;
    }

    QString actualInfo = info.mid(5);//删去前面的“学生信息：”

    QStringList part=actualInfo.split('/');

    if(part.size() >= 8) {
        QString studentId = part[0];

        if(currentStudentId.isEmpty() || currentStudentId == studentId)
        {
            ui->ID->setText(part[0]);

            ui->NAME->setText(part[1]);

            ui->GENDER->setText(part[2]);

            ui->AGE->setText(part[3]);

            ui->MAJORS->setText(part[4]);

            ui->CLASS->setText(part[5]);

            ui->PHONENUM->setText(part[6]);

            ui->ADDRESS->setText(part[7]);

            StudentInfo studentInfo;

            studentInfo.id = part[0];

            studentInfo.name = part[1];

            studentInfo.gender = part[2];

            studentInfo.age = part[3];

            studentInfo.major = part[4];

            studentInfo.className = part[5];

            studentInfo.phone = part[6];

            studentInfo.address = part[7];

            bool saveSuccess = StudentManager::instance().addOrUpdateStudent(studentInfo);

            if(saveSuccess)
            {
                qDebug() << "学生信息已保存到本地：" << studentId;

                // 如果当前窗口显示的就是这个学生，更新窗口标题
                if(currentStudentId == studentId)
                {
                    setWindowTitle("个人中心 - " + studentId);
                }
            }
            else
            {
                qDebug() << "保存学生信息失败：" << studentId;
            }
        }
        else
        {
            qDebug() << "收到其他学生信息，当前学生：" << currentStudentId
                     << "，收到：" << studentId;

            StudentInfo studentInfo;

            studentInfo.id = part[0];

            studentInfo.name = part[1];

            studentInfo.gender = part[2];

            studentInfo.age = part[3];

            studentInfo.major = part[4];

            studentInfo.className = part[5];

            studentInfo.phone = part[6];

            studentInfo.address = part[7];

            StudentManager::instance().addOrUpdateStudent(studentInfo);

            qDebug() << "已保存其他学生信息到本地：" << studentId;

        }

    }
    else
    {
        qDebug() << "学生信息格式错误，字段数量不足：" << part.size();
        qDebug() << "实际内容：" << actualInfo;
    }
}

void Student::on_EditStudent_clicked()
{
    if (currentStudentId.isEmpty()) {
        QMessageBox::warning(this, "警告", "学号未设置！");
        return;
    }
    // 创建编辑窗口
    StudentInfoEdit *editWindow = new StudentInfoEdit(currentStudentId);

    // 连接信号
    connect(editWindow, &StudentInfoEdit::editCompleted, this, [this](const QString &studentId) {
        // 编辑完成，重新加载学生信息
        loadStudentInfoFromLocal();
        qDebug() << "学生" << studentId << "信息已更新";
    });

    connect(editWindow, &StudentInfoEdit::editCancelled, this, [this]() {
        qDebug() << "编辑已取消";
    });

    // 显示编辑窗口
    editWindow->show();

    // 设置窗口关闭时自动删除
    editWindow->setAttribute(Qt::WA_DeleteOnClose);
}

