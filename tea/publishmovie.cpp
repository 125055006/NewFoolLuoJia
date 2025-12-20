#include "publishmovie.h"
#include "ui_publishmovie.h"

PublishMovie::PublishMovie(MyServer *server,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PublishMovie)
    ,m_server(server)
{
    ui->setupUi(this);
}

PublishMovie::~PublishMovie()
{
    delete ui;
}

void PublishMovie::on_Return_clicked()
{
    this->close();
}


void PublishMovie::on_Publish_clicked()
{
    QString movieInfo="电影信息";
    movieInfo+=ui->film1->text();
    movieInfo+='/';
    movieInfo+=ui->film2->text();
    movieInfo+='/';
    movieInfo+=ui->film3->text();
    movieInfo+='/';
    movieInfo+=ui->film4->text();
    movieInfo+='/';
    movieInfo+=ui->film5->text();
    movieInfo+='/';
    movieInfo+=ui->time1->text();
    movieInfo+='/';
    movieInfo+=ui->time2->text();
    movieInfo+='/';
    movieInfo+=ui->time3->text();
    movieInfo+='/';
    movieInfo+=ui->time4->text();
    movieInfo+='/';
    movieInfo+=ui->time5->text();
    movieInfo+='/';
    movieInfo+=ui->place1->text();
    movieInfo+='/';
    movieInfo+=ui->place2->text();
    movieInfo+='/';
    movieInfo+=ui->place3->text();
    movieInfo+='/';
    movieInfo+=ui->place4->text();
    movieInfo+='/';
    movieInfo+=ui->place5->text();
    qDebug()<<"已发送"<<movieInfo;
    m_server->sendToAllClients(movieInfo);
    QMessageBox::warning(this,"提示","发布成功");
}

