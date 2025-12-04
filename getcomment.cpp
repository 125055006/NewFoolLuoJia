#include "getcomment.h"
#include "ui_getcomment.h"

GetComment::GetComment(MyServer *server,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GetComment)
    ,m_server(server)
{
    ui->setupUi(this);
    connect(m_server,&MyServer::SendCom_Info,this,&GetComment::GetCom);
}

GetComment::~GetComment()
{
    delete ui;
}

void GetComment::GetCom(const QString &com_Info)
{
    QStringList part=com_Info.split('/');
    ui->TeaName->setText(part[0]);
    ui->content->setText(part[1]);
}
void GetComment::on_pushButton_clicked()
{
    this->close();
}


void GetComment::on_confirm_clicked()
{
    QString confirm="收到";
    m_server->sendToAllClients(confirm);
}

