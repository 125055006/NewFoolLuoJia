#include "mentalheal.h"
#include "ui_mentalheal.h"
#include<vector>
using namespace std;
MentalHeal::MentalHeal(MyClient *client,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MentalHeal)
    ,m_client(client)
{
    ui->setupUi(this);
    QButtonGroup *teaGroup=new QButtonGroup(this);   //创建按钮组
    teaGroup->addButton(ui->tea1);
    teaGroup->addButton(ui->tea2);
    teaGroup->addButton(ui->tea3);           //添加按钮
    connect(teaGroup,&QButtonGroup::buttonClicked,[=](QAbstractButton *selectedBtn)     //监听选项变化，并用lambda表达式
            {
        teas.clear();
        teas.push_back(selectedBtn->text());

    });
}

MentalHeal::~MentalHeal()
{
    delete ui;
}



void MentalHeal::on_Send_clicked()
{
    QString mt_Info="心预信息";
    mt_Info+=ui->name->text();
    mt_Info+='/';
    mt_Info+=teas[0];
    mt_Info+='/';
    mt_Info+=ui->time->text();
    mt_Info+='/';
    mt_Info+=ui->situation->toPlainText();
    m_client->sendMessage(mt_Info);
    QMessageBox::warning(this,"提示","预约成功");
}


void MentalHeal::on_Return_2_clicked()
{
    this->close();
}

