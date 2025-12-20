#include "teadorm.h"
#include "ui_teadorm.h"

TeaDorm::TeaDorm(MyServer *server, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TeaDorm)
{
    ui->setupUi(this);
    m_server = server;
    distri = new DormDistribute(m_server);
    tofix = new DormToFix(m_server);

    //传递名字信息的connect
    connect(this, &TeaDorm::sendToDistri, distri, &DormDistribute::getName);
    //常规：实现hide和show的交互的connect
    connect(distri, &DormDistribute::distriHadExit, this, &TeaDorm::show);
    connect(tofix, &DormToFix::dormtofixHadExit, this, &TeaDorm::show);

    this->setWindowTitle("宿舍大调查");
}

TeaDorm::~TeaDorm()
{
    delete ui;
}

void TeaDorm::on_exitButton_clicked()
{
    this->close();
    emit dormHadExit();
}


void TeaDorm::on_distributeButton_clicked()
{
    distri->show();
    this->hide();
}


void TeaDorm::on_toFixButton_clicked()
{
    tofix->show();
    this->hide();
}

