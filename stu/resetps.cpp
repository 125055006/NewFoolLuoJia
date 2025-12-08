#include "resetps.h"
#include "ui_resetps.h"

ResetPS::ResetPS(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ResetPS)
{
    ui->setupUi(this);
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
    QString id=ui->ReIDedit->text();
    QString Ps=ui->RePSedit->text();
    QString re_Ps=ui->Reconfirm->text();
    if(Ps==re_Ps)
    {
        emit SendNewIdAndPs(id,Ps);
        QMessageBox::warning(this,"提示","修改成功");
    }
    else
    {
        QMessageBox::warning(this,"错误","前后密码不一致");
        ui->Reconfirm->clear();
    }
}

