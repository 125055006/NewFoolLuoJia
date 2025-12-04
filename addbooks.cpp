#include "addbooks.h"
#include "ui_addbooks.h"

AddBooks::AddBooks(MyServer *server,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddBooks)
    ,m_server(server)
{
    ui->setupUi(this);
    books={{"三国演义","三大家族的恩怨情仇",false},{"红楼梦","回家探亲，不小心攻略了表哥",false},{"水浒传","105个男人和3个女人",false},{"西游记","总有反派想抢我师傅",false}};
}

AddBooks::~AddBooks()
{
    delete ui;
}

void AddBooks::on_Return_clicked()
{
    this->close();
}


void AddBooks::on_add_clicked()
{
    book target;
    QString Book_Info="书籍信息";
    target.name=ui->nameEdit->text();
    target.introduce=ui->introduce->toPlainText();
    target.isBorrowed=false;
    Book_Info+=target.name;
    Book_Info+='/';
    Book_Info+=target.introduce;

    QMessageBox::warning(this,"提示","添加成功");
    books.append(target);
    m_server->sendToAllClients(Book_Info);
    qDebug()<<"添加成功，现在共有"<<books.size()<<"本书";
    for(int i=0;i<books.size();i++)
    {
        qDebug()<<books[i].name<<" ";
    }
    emit SendToLib(books);

}

