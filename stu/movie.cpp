#include "movie.h"
#include "ui_movie.h"

movie::movie(MyClient *client,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::movie)
    ,m_client(client)
{
    ui->setupUi(this);
    connect(m_client,&MyClient::SendMovieInfo,this,&movie::ShowMovie);
}

movie::~movie()
{
    delete ui;
}

void movie::on_Return_clicked()
{
    this->close();
}

void movie::ShowMovie(const QString &Movie_Info)
{
    QStringList part=Movie_Info.split('/');
    for(int i=0;i<part.size();i++)
    {
        switch(i+1)
        {
        case 1:
            ui->film1->setText(part[0]);
            break;
        case 2:
            ui->film2->setText(part[1]);
            break;
        case 3:
            ui->film3->setText(part[2]);
            break;
        case 4:
            ui->film4->setText(part[3]);
            break;
        case 5:
            ui->film5->setText(part[4]);
            break;
        case 6:
            ui->time1->setText(part[5]);
            break;
        case 7:
            ui->time2->setText(part[6]);
            break;
        case 8:
            ui->time3->setText(part[7]);
            break;
        case 9:
            ui->time4->setText(part[8]);
            break;
        case 10:
            ui->time5->setText(part[9]);
            break;
        case 11:
            ui->place1->setText(part[10]);
            break;
        case 12:
            ui->place2->setText(part[11]);
            break;
        case 13:
            ui->place3->setText(part[12]);
            break;
        case 14:
            ui->place4->setText(part[13]);
            break;
        case 15:
            ui->place5->setText(part[14]);
            break;
        }
    }
}
