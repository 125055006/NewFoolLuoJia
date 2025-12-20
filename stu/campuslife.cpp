#include "campuslife.h"
#include "ui_campuslife.h"

CampusLife::CampusLife(MyClient *client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CampusLife)
{
    ui->setupUi(this);
    m_client = client;

    dorm = new StuDorm(m_client);
    bank = new StuBank(m_client);
    //父页面和子页面show和hide的交互
    connect(dorm, &StuDorm::dormHadExit, this, &CampusLife::show);
    connect(bank, &StuBank::bankHadExit, this, &CampusLife::show);

    this->setWindowTitle("那很有生活");
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


void CampusLife::on_eCardButton_clicked()
{
    bank->show();
    this->hide();
}

