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
    //connect(m_server,&MyServer::SendTargetBook,this,&OnlineLib::AnswerRequest);
}

OnlineLib::~OnlineLib()
{
    delete ui;
}

/*void OnlineLib::AnswerRequest(const QString &target)
{
    bool isFound=false;
    ans="借书回复";
    for(int i=0;i<add_books->books.size();i++)
    {
        if(add_books->books[i].name==target)
        {
            if(!add_books->books[i].isBorrowed)
            {
                isFound=true;
                add_books->books[i].isBorrowed=true;
                ans+=add_books->books[i].introduce;
                break;
            }
            if(add_books->books[i].isBorrowed)
            {
                isFound=true;
                ans+="被借了";
                break;
            }
        }
    }
    if(!isFound)
    {
        ans+="没找到";
    }
    m_server->sendToAllClients(ans);
    qDebug()<<"已回复"<<ans;
}*/
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

