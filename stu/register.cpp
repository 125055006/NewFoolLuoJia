#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);

    ui->NewPasswords->setEchoMode(QLineEdit::Password);

    ui->ConfirmNewPasswords->setEchoMode(QLineEdit::Password);
}

Register::~Register()
{
    delete ui;
}


void Register::on_ConfirmRegister_clicked()
{
        QString id=ui->NewUserName->text().trimmed();

    QString Ps=ui->NewPasswords->text();

    QString re_Ps=ui->ConfirmNewPasswords->text();

    if (id.isEmpty()) {
        QMessageBox::warning(this, "错误", "请输入账号");
        return;
    }

    if (Ps.isEmpty()) {
        QMessageBox::warning(this, "错误", "请输入新密码");
        return;
    }

    if (re_Ps.isEmpty()) {
        QMessageBox::warning(this, "错误", "请再次输入新密码");
        return;
    }

    if (UserFileManager::instance().userExists(id)) {
        QMessageBox::warning(this, "错误", "用户名已存在");
        return;
    }

    if(Ps != re_Ps)
    {
        QMessageBox::warning(this,"错误","前后密码不一致");
        ui->ConfirmNewPasswords->clear();
        ui->ConfirmNewPasswords->setFocus();
        return;
    }

    bool success = UserFileManager::instance().addUser(id, Ps);

    if (success) {
        QMessageBox::information(this, "成功", "用户注册成功！");

        emit RegisterSuccess();

        ui->NewUserName->clear();
        ui->NewPasswords->clear();
        ui->ConfirmNewPasswords->clear();

        this->close();
    }
    else
    {
        QMessageBox::warning(this, "错误", "用户注册失败，请重试");
    }
}

