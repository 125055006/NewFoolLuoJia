#include "stu_comment.h"
#include "ui_stu_comment.h"

stu_comment::stu_comment(MyClient *client,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::stu_comment)
    ,m_client(client)
{
    ui->setupUi(this);
    com_Info="教评信息";
    connect(m_client,&MyClient::ReturnAnswer,this,&stu_comment::Resepon);
}

stu_comment::~stu_comment()
{
    delete ui;
}

void stu_comment::on_Return_clicked()
{
    this->close();
}
void stu_comment::Resepon()
{
    QMessageBox::warning(this,"提示","我们已收到你的反馈");
}

void stu_comment::on_confirm_clicked()
{
    com_Info+=ui->teaEdit->text();
    com_Info+='/';
    com_Info+=ui->contentEdit->toPlainText();
    m_client->sendMessage(com_Info);
    QMessageBox::warning(this,"喜报","恭喜！评价成功");
}

