#include "stumenu.h"
#include "ui_stumenu.h"

StuMenu::StuMenu(MyClient *client,Student *student,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StuMenu)
    ,stu(student)
    ,m_client(client)
{
    ui->setupUi(this);
    cos_cos=new ChooseCourse(m_client);
    con_sco=new ConsultScore(m_client);
    stu_com=new stu_comment(m_client);
    bor_book=new BorrowBook(m_client);
    con_sco->setChooseCourse(cos_cos);
}

StuMenu::~StuMenu()
{
    delete ui;
}

void StuMenu::on_PersonCenter_clicked()
{
    if(stu)
    {
        stu->show();
    }
}


void StuMenu::on_choose_course_clicked()
{
    cos_cos->show();
}


void StuMenu::on_Con_Sco_clicked()
{
    con_sco->show();
}


void StuMenu::on_stu_com_clicked()
{
    stu_com->show();
}


void StuMenu::on_bor_book_clicked()
{
    bor_book->show();
}

