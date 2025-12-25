#include "student.h"
#include "ui_student.h"
#include "studentinfoedit.h"  // 添加头文件
#include "studentmanager.h"     // 添加头文件
#include <QDebug>
#include <QMenu>      // 添加：用于右键菜单
#include <QAction>
#include <QFile>

Student::Student(MyClient *client,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Student)
    ,m_client(client)
    , refreshAction(nullptr)
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

    this->setContextMenuPolicy(Qt::CustomContextMenu);

    createContextMenu();

    if(m_client)     //连接信号到槽函数
    {
        connect(m_client,&MyClient::ReceiveStuInfo,this,&Student::onReceiveStuInfo);
    }

    connect(ui->RefreshBtn, &QPushButton::clicked, this, &Student::on_RefreshBtn_clicked);
}

Student::~Student()
{
    delete ui;
    if (refreshAction) delete refreshAction;
}

void Student::createContextMenu()
{
    // 创建刷新动作
    refreshAction = new QAction("刷新学生信息", this);
    refreshAction->setShortcut(QKeySequence("F5"));  // 设置快捷键F5
    refreshAction->setIcon(QIcon::fromTheme("view-refresh"));

    // 连接动作信号
    connect(refreshAction, &QAction::triggered, this, &Student::onRefreshAction);

    // 设置窗口的右键菜单策略
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    // 连接自定义上下文菜单请求信号
    connect(this, &Student::customContextMenuRequested, this, [this](const QPoint &pos){
        QMenu menu(this);
        menu.addAction(refreshAction);
        menu.exec(this->mapToGlobal(pos));
    });
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

    QString dataFile = "config/studentsinfo.dat";
    qDebug() << "加载文件：" << dataFile;
    qDebug() << "文件是否存在：" << QFile::exists(dataFile);

    StudentManager::instance().loadFromFile();

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


void Student::on_RefreshBtn_clicked()
{
    refreshStudentInfo();
}

void Student::onRefreshAction()
{
    refreshStudentInfo();
}

void Student::refreshStudentInfo()
{
    if (currentStudentId.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先设置学号！");
        return;
    }

    qDebug() << "正在刷新学生信息，学号：" << currentStudentId;

    // 先尝试从本地加载

    ui->NAME->clear();
    ui->GENDER->clear();
    ui->AGE->clear();
    ui->MAJORS->clear();
    ui->CLASS->clear();
    ui->PHONENUM->clear();
    ui->ADDRESS->clear();

    QApplication::processEvents();

    loadStudentInfoFromLocal();

    // 如果已连接服务器，发送请求获取最新信息
    if (m_client) {
        // 发送请求到服务器获取最新信息
        m_client->requestStudentInfo(currentStudentId);
        qDebug() << "已向服务器发送学生信息请求：" << currentStudentId;

       QMessageBox::information(this, "提示", "已向服务器请求最新信息，请稍候...");
    } else {
        qDebug() << "客户端未连接，仅从本地加载信息";
        QMessageBox::information(this, "提示",
                                 "学生信息已刷新（仅本地数据）！\n未连接服务器，无法获取最新信息。");
        return;
    }

    // 注意：这里不显示成功提示，因为需要等待服务器响应
    // 服务器响应后会触发 onReceiveStuInfo 槽函数自动更新界面
}

void Student::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(refreshAction);
    menu.exec(event->globalPos());
}
