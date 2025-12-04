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

