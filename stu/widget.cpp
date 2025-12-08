#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    Cur_id="1";
    Cur_Ps="1";
    ui->setupUi(this);
    set_ps=new ResetPS;
    client=new MyClient;
    stu_ui=new Student(client);        //让student连接信号
    cos_client=new ChooseCourse(client);
    stu_menu=new StuMenu(client,stu_ui);
    con_sco=new ConsultScore(client);
    stu_com=new stu_comment(client);
    con_sco->setChooseCourse(cos_client);
    client->connectToServer("127.0.0.1",9988);
    client->sendMessage("testing...");
    ui->login->setShortcut(Qt::Key_Return);
    connect(set_ps,&ResetPS::SendNewIdAndPs,this,&Widget::NewIdAndPs);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::NewIdAndPs(const QString &new_id,const QString &new_ps)
{
    Cur_id=new_id;
    Cur_Ps=new_ps;
}
void Widget::on_login_clicked()
{
    QString id=ui->idEdit->text();
    QString passward=ui->PasswardEdit->text();
    if(id==Cur_id&&passward==Cur_Ps)
    {
        stu_menu->show();
    }
    else
    {
        QMessageBox::warning(this,"错误","账号或密码错误");
    }
}


void Widget::on_ResetPS_clicked()
{
    set_ps->show();
}

