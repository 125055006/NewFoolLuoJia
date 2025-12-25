#include "studorm.h"
#include "ui_studorm.h"

StuDorm::StuDorm(MyClient *client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StuDorm)
{
    ui->setupUi(this);
    m_client = client;
    exchange = new DormExchange(m_client);
    fix = new DormFix(m_client);

    //常规：实现hide和show的connect
    connect(exchange, &DormExchange::exchangeHadExit, this, &StuDorm::show);
    connect(fix, &DormFix::fixHadExit, this, &StuDorm::show);
    //读取当前宿舍信息的connect
    connect(m_client, &MyClient::sendDistriInfo, this, &StuDorm::onReciveDorm);
    //把宿舍维修信息在这里提示，提高信息的时效性
    connect(m_client, &MyClient::getFixTime, this, &StuDorm::fixTimeGet);

    this->setWindowTitle("宿舍");
}

StuDorm::~StuDorm()
{
    delete ui;
}

void StuDorm::on_exitButton_clicked()
{
    this->close();
    emit dormHadExit();
}


void StuDorm::on_dormExchangeButton_clicked()
{
    exchange->show();
    this->hide();
}


void StuDorm::on_fixButton_clicked()
{
    fix->show();
    this->hide();
}


void StuDorm::onReciveDorm(const QString &Info) {
    ui->showLineEdit->setText(Info);
}

void StuDorm::fixTimeGet(const QString &Info) {
    qDebug() << "报修时间" << Info;
    QMessageBox::information(this, "好耶", "报修时间：" + Info);
}
