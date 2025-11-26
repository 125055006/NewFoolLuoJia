#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    re_cord=new Record;
    server=new MyServer;
    if(server->startServer(9988))
    {
        qDebug()<<"启动成功";
    }
    else
    {
        qDebug()<<"启动失败";
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_Record_clicked()
{
    re_cord->show();
}

