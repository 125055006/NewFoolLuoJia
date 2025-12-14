#include "bus.h"
#include "ui_bus.h"

Bus::Bus(MyClient *client,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Bus)
    ,m_client(client)
{
    ui->setupUi(this);
    QPixmap DefaultPic(":/images/bus1.png");
    ui->img->setPixmap(DefaultPic.scaled(ui->img->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));        //图片自适应大小
}

Bus::~Bus()
{
    delete ui;
}

void Bus::on_Return_clicked()
{
    this->close();
}


void Bus::on_bus1_clicked()
{
    QPixmap pic1(":/images/bus1.png");
    ui->img->setPixmap(pic1.scaled(ui->img->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
}


void Bus::on_bus2_clicked()
{
    QPixmap pic2(":/images/bus2.png");
    ui->img->setPixmap(pic2.scaled(ui->img->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
}


void Bus::on_bus3_clicked()
{
    QPixmap pic3(":/images/bus3.png");
    ui->img->setPixmap(pic3.scaled(ui->img->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
}

