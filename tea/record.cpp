#include "record.h"
#include "ui_record.h"
#include <QDebug>
#include <QMessageBox>

Record::Record(MyServer *server,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Record)
    ,server(server)
{

    ui->setupUi(this);
    //connect(server,&MyServer::GetStuInfo,this,&Record::onGetStuInfo);

    setupConnections();//添加一个回车快捷键
}

Record::~Record()
{
    delete ui;
}

void Record::setupConnections()
{
    // 按回车键快速跳转到下一个输入框
    ui->idEdit->setFocus();

    // 连接回车键信号
    connect(ui->idEdit, &QLineEdit::returnPressed, [this]() { ui->nameEdit->setFocus(); });
    connect(ui->nameEdit, &QLineEdit::returnPressed, [this]() { ui->sexEdit->setFocus(); });
    connect(ui->sexEdit, &QLineEdit::returnPressed, [this]() { ui->ageEdit->setFocus(); });
    connect(ui->ageEdit, &QLineEdit::returnPressed, [this]() { ui->majorEdit->setFocus(); });
    connect(ui->majorEdit, &QLineEdit::returnPressed, [this]() { ui->classEdit->setFocus(); });
    connect(ui->classEdit, &QLineEdit::returnPressed, [this]() { ui->phoneEdit->setFocus(); });
    connect(ui->phoneEdit, &QLineEdit::returnPressed, [this]() { ui->addressEdit->setFocus(); });
    connect(ui->addressEdit, &QLineEdit::returnPressed, this, &Record::on_Save_clicked);
}

void Record::on_Save_clicked()
{
    QString id = ui->idEdit->text().trimmed();
    QString name = ui->nameEdit->text().trimmed();
    QString sex = ui->sexEdit->text().trimmed();
    QString age = ui->ageEdit->text().trimmed();
    QString major = ui->majorEdit->text().trimmed();
    QString Class = ui->classEdit->text().trimmed();
    QString phone = ui->phoneEdit->text().trimmed();
    QString address = ui->addressEdit->text().trimmed();

    //学号不可以是空的
    if(id.isEmpty()) {
        QMessageBox::warning(this, "警告", "学号不能为空");
        ui->idEdit->setFocus();
        return;
    }

    //姓名不可以是空的
    if(name.isEmpty()) {
        QMessageBox::warning(this, "警告", "姓名不能为空");
        ui->nameEdit->setFocus();
        return;
    }

    //创建学生信息对象info
    StudentInfo info;
    info.id = id;
    info.name = name;
    info.gender = sex;
    info.age = age;
    info.major = major;
    info.className = Class;
    info.phone = phone;
    info.address = address;

    //判断是否已经存在
    bool exists = StudentManager::instance().exists(id);

    //如果存在
    if(exists) {
        // 询问是否修改
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "确认",
                                      QString("学号【%1】已存在，是否修改该学生信息？").arg(id),
                                      QMessageBox::Yes | QMessageBox::No);

        if(reply == QMessageBox::No) {
            ui->idEdit->clear();
            ui->idEdit->setFocus();
            return;
        }
    }

    //最后保存到本地文件（重复则修改，不重复则添加）
    bool saveSuccess = StudentManager::instance().addOrUpdateStudent(info);

    if(!saveSuccess) {
        QMessageBox::critical(this, "错误", "保存学生信息失败！");
        return;
    }

    // 构造信息字符串
    QString infoStr = info.toString();

    qDebug() << (exists ? "修改" : "添加") << "学生信息：" << id << name;
    qDebug() << "信息内容：" << infoStr;

    // 发送到所有客户端（网络通知）
    if(server) {
        QString message = "学生信息:" + infoStr;  // 添加前缀便于识别
        server->sendToAllClients(message);
        qDebug() << "信息已发送给学生端";
    }

    emit sendStuInfo(infoStr);
    emit sendToDorm(name);

    clearAllInputs();

    QString msg = exists ?
                      QString("成功修改学生【%1 - %2】的信息！").arg(id, name) :
                      QString("成功添加新学生【%1 - %2】！").arg(id, name);

    QMessageBox::information(this, "操作成功", msg);

    ui->idEdit->setFocus();

}

void Record::clearAllInputs()
{
    // 添加这个函数的具体实现
    ui->idEdit->clear();
    ui->nameEdit->clear();
    ui->sexEdit->clear();
    ui->ageEdit->clear();
    ui->majorEdit->clear();
    ui->classEdit->clear();
    ui->phoneEdit->clear();
    ui->addressEdit->clear();
}

void Record::on_Cancel_clicked()
{
    this->close();
}

