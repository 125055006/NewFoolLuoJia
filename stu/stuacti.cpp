#include "stuacti.h"
#include "ui_stuacti.h"

StuActi::StuActi(MyClient* client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StuActi)
{
    ui->setupUi(this);
    m_client = client;
    rec = new StuActiRec(m_client);
    join = new StuActiJoin(m_client);

    this->setWindowTitle("社团活动");

    connect(rec, &StuActiRec::recExit, this, &StuActi::show);
    connect(join, &StuActiJoin::joinExit, this, &StuActi::show);
}

StuActi::~StuActi()
{
    delete ui;
}

void StuActi::on_exitButton_clicked()
{
    this->close();
}


void StuActi::on_recordButton_clicked()
{
    this->hide();
    rec->show();
}


void StuActi::on_joinButton_clicked()
{
    this->hide();
    join->show();
}

