#include "dormtofix.h"
#include "ui_dormtofix.h"

DormToFix::DormToFix(MyServer *server, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DormToFix)
{
    ui->setupUi(this);
    m_server = server;

    //设置占位符提示用户
    ui->timeLineEdit->setPlaceholderText("请输入预计维修时间");
    ui->reasonLineEdit->setPlaceholderText("暂无报修请求");

    //接收学生端发来的报修信息 并显示在LineEdit上
    connect(m_server, &MyServer::reciveFix, this, &DormToFix::displayFixInfo);

    this->setWindowTitle("无敌破坏王");
}

DormToFix::~DormToFix()
{
    delete ui;
}

void DormToFix::on_exitButton_clicked()
{
    this->close();
    emit dormtofixHadExit();
}

void DormToFix::displayFixInfo(const QString &Info) {
    //QStringList读取Info中的信息
    QStringList part = Info.split("/");

    ui->reasonLabel->setText(part[0] + ";" + part[1]);
    ui->alarmLabel->setText(part[2]);
}

void DormToFix::on_commitButton_clicked()
{
    //仅读取reasonLineEdit是否为空 判断是否有请求
    if (!ui->reasonLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "闲？", "目前还未有请求");
        qDebug() << "无请求，无需确认报修信息";
        return;
    }

    QString time = ui->timeLineEdit->text();
    if (time.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先设置报修时间");
        return;
    }

    m_server->sendToAllClients("报修时间" + time);
}

