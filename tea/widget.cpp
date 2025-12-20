#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    server=new MyServer;
    if(server->startServer(9988))
    {
        qDebug()<<"启动成功";
    }
    else
    {
        qDebug()<<"启动失败";
    }
    re_cord=new Record(server);
    stu_check=new StuCheck(re_cord);
    add_score=new AddScore(server);
    get_com=new GetComment(server);
    online_lib=new OnlineLib(server);
    tea_club = new TeaClub(server);
    campus = new CampusLife(server);

    connect(campus, &CampusLife::campusHadExit, this, &Widget::show);
    //这个connect连接record和dorm 为了读取学生的名字
    connect(re_cord, &Record::sendToDorm, campus, &CampusLife::sendToDorm);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_Record_clicked()
{
    re_cord->show();
}


void Widget::on_StuCheck_clicked()
{
    stu_check->show();
}


void Widget::on_AddScore_clicked()
{
    add_score->show();
}


void Widget::on_Look_com_clicked()
{
    get_com->show();
}


void Widget::on_book_mng_clicked()
{
    online_lib->show();
}


void Widget::on_clubButton_clicked()
{
    tea_club->show();
}


void Widget::on_campusButton_clicked()
{
    campus->show();
    this->hide();
}

