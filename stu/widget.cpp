#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    set_ps = new ResetPS;

    client = new MyClient;

    stu_ui = new Student(client);//让student连接信号

    cos_client = new ChooseCourse(client);

    stu_menu = new StuMenu(client,stu_ui);

    con_sco = new ConsultScore(client);

    stu_com = new stu_comment(client);

    Register_New =new Register;

    con_sco->setChooseCourse(cos_client);

    //连接服务器

    client->connectToServer("127.0.0.1",9988);

    client->sendMessage("testing...");

    ui->login->setShortcut(Qt::Key_Return);
    //密码设置为小圆点
    ui->PasswardEdit->setEchoMode(QLineEdit::Password);

    connect(set_ps, &ResetPS::passwordResetSuccess, this, [this]() {
        QMessageBox::information(this, "提示", "密码已重置，请使用新密码登录");
    });

    connect(Register_New, &Register::RegisterSuccess, this, [this]() {
        QMessageBox::information(this, "提示", "用户已成功注册，请登录");
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_login_clicked()
{
    QString id=ui->idEdit->text().trimmed();;

    QString password=ui->PasswardEdit->text();

    bool isValid = UserFileManager::instance().validateUser(id, password);

    if(isValid)
    {
        stu_ui->setStudentId(id);

        stu_menu->show();
        this->hide();
    }

    else
    {
        QMessageBox::warning(this,"错误","账号或密码错误");
    }
}


void Widget::on_ResetPS_clicked()
{
    set_ps->show();
}


void Widget::on_CreatUsers_clicked()
{
    Register_New->show();
}

