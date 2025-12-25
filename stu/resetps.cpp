#include "resetps.h"
#include "ui_resetps.h"

ResetPS::ResetPS(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ResetPS)
{
    ui->setupUi(this);

    ui->RePSedit->setEchoMode(QLineEdit::Password);

    ui->Reconfirm->setEchoMode(QLineEdit::Password);

}

ResetPS::~ResetPS()
{
    delete ui;
}

void ResetPS::on_Return_clicked()
{
    this->close();
}


void ResetPS::on_Confirm_clicked()
{
    QString id=ui->ReIDedit->text().trimmed();

    QString Ps=ui->RePSedit->text();

    QString re_Ps=ui->Reconfirm->text();

    //验证输入

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

    if (!UserFileManager::instance().userExists(id)) {
        QMessageBox::warning(this, "错误", "用户不存在");
        return;
    }

    if(Ps != re_Ps)
    {
        QMessageBox::warning(this,"错误","前后密码不一致");
        ui->Reconfirm->clear();
        ui->Reconfirm->setFocus();
        return;
    }

    bool success = UserFileManager::instance().resetPassword(id, Ps);

    if (success) {
        QMessageBox::information(this, "成功", "密码重置成功！");

        emit passwordResetSuccess();

        ui->ReIDedit->clear();
        ui->RePSedit->clear();
        ui->Reconfirm->clear();

        this->close();
    }
    else
    {
        QMessageBox::warning(this, "错误", "密码重置失败，请重试");
    }

}

