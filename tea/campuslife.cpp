#include "campuslife.h"
#include "ui_campuslife.h"

CampusLife::CampusLife(MyServer *server, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CampusLife)
{
    ui->setupUi(this);
    m_server = server;
    dorm = new TeaDorm(m_server);
    bank = new TeaBank(m_server);

    //show hide 交互
    connect(dorm, &TeaDorm::dormHadExit, this, &CampusLife::show);
    connect(bank, &TeaBank::bankHadExit, this, &CampusLife::show);
    //发送名字信息
    connect(this, &CampusLife::sendToDorm, dorm, &TeaDorm::sendToDistri);
}

CampusLife::~CampusLife()
{
    delete ui;
}

void CampusLife::on_dormButton_clicked()
{
    dorm->show();
    this->hide();
}


void CampusLife::on_exitButton_clicked()
{
    this->close();
    emit campusHadExit();
}


void CampusLife::on_bankButton_clicked()
{
    bank->show();
    this->hide();
}

