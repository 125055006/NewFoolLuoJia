#include "stumenu.h"
#include "ui_stumenu.h"

StuMenu::StuMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StuMenu)
{
    ui->setupUi(this);
    stu=new Student;
}

StuMenu::~StuMenu()
{
    delete ui;
}

void StuMenu::on_PersonCenter_clicked()
{
    stu->show();
}

