#include "answer_mth.h"
#include "ui_answer_mth.h"

Answer_MTH::Answer_MTH(MyServer *server,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Answer_MTH)
    ,m_server(server)
{
    ui->setupUi(this);
    connect(m_server,&MyServer::SendMTH,this,&Answer_MTH::ShowMTH);
}

Answer_MTH::~Answer_MTH()
{
    delete ui;
}

void Answer_MTH::ShowMTH(const QString &MTH_Info)
{
    QStringList part=MTH_Info.split('/');
    ui->name->setText(part[0]);
    ui->tea->setText(part[1]);
    ui->time->setText(part[2]);
    ui->situation->setText(part[3]);
}

void Answer_MTH::on_Return_clicked()
{
    this->close();
}

