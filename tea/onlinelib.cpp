#include "onlinelib.h"
#include "ui_onlinelib.h"

OnlineLib::OnlineLib(MyServer *server,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OnlineLib)
    ,m_server(server)
{
    ui->setupUi(this);
    add_books=new AddBooks(m_server);
    connect(add_books,&AddBooks::SendToLib,this,&OnlineLib::ShowBooks);
}

OnlineLib::~OnlineLib()
{
    delete ui;
}

void OnlineLib::on_Return_clicked()
{
    this->close();
}

void OnlineLib::ShowBooks(QList<book> &books)
{
    QString target=ui->nameEdit->text();
    bool isFound=false;
    for(int i=0;i<books.size();i++)
    {
        if(books[i].name==target)
        {
            ui->introduce->setText(books[i].introduce);
            isFound=true;
            qDebug()<<"找到了";
            qDebug()<<books[i].name;
            qDebug()<<books[i].introduce;
            break;
        }
    }
    if(!isFound)
    {
        QMessageBox::warning(this,"提示","未找到这本书");
    }
}

void OnlineLib::on_AddBooks_clicked()
{
    add_books->show();
}


void OnlineLib::on_find_clicked()
{
    ShowBooks(add_books->books);
}


void OnlineLib::on_delete_2_clicked()
{
    QString target=ui->nameEdit->text();
    bool isDeleted=false;
    for(int i=0;i<add_books->books.size();i++)
    {
        if(add_books->books[i].name==target)
        {
            add_books->books.removeAt(i);
            isDeleted=true;
            break;
        }
    }
    if(isDeleted)
    {
        QMessageBox::warning(this,"提示","删除成功");
        add_books->saveBooks();
        //同步到文件
    }
    else
    {
        QMessageBox::warning(this,"提示","删除失败");
    }
}

