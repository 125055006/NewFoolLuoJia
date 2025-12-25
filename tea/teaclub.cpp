#include "teaclub.h"
#include "ui_teaclub.h"

TeaClub::TeaClub(MyServer *server, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TeaClub)
{
    ui->setupUi(this);
    m_server = server;
    pub = new TeaClubPub(m_server);
    comi = new TeaClubComi(m_server);

    connect(pub, &TeaClubPub::pubHadExit, this, &TeaClub::show);
    connect(comi, &TeaClubComi::comiHadExit, this, &TeaClub::show);
    connect(pub, &TeaClubPub::needCommit, comi, &TeaClubComi::toDoNew);

    this->setWindowTitle("社团活动管理");
}

TeaClub::~TeaClub()
{
    delete ui;
}

void TeaClub::on_exitButton_clicked()
{
    this->close();
}


void TeaClub::on_publishButton_clicked()
{
    pub->show();
    this->hide();
}


void TeaClub::on_commitButton_clicked()
{
    comi->show();
    this->hide();
}

