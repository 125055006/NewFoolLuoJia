#include "borrowbook.h"
#include "ui_borrowbook.h"
BorrowBook::BorrowBook(MyClient *client,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BorrowBook)
    ,m_client(client)
{
    ui->setupUi(this);
    books={{"三国演义","三大家族的恩怨情仇",false},{"红楼梦","回家探亲，不小心攻略了表哥",false},{"水浒传","105个男人和3个女人",false},{"西游记","总有反派想抢我师傅",false}};
    connect(m_client,&MyClient::SendBookInfo,this,&BorrowBook::UpdataBooks);
    //connect(m_client,&MyClient::SendBookAns,this,&BorrowBook::Result);
}

BorrowBook::~BorrowBook()
{
    delete ui;
}

void BorrowBook::UpdataBooks(const QString &Book_Info)
{
    QStringList part=Book_Info.split('/');
    book NewBook;
    NewBook.name=part[0];
    NewBook.introduce=part[1];
    NewBook.isBorrowed=false;
    books.append(NewBook);
}
/*void BorrowBook::Result(const QString &ans)
{
    if(ans=="没找到")
    {
        QMessageBox::warning(this,"提示","未找到该书籍");
    }
    else if(ans=="被借了")
    {
        QMessageBox::warning(this,"提示","该书籍已被借阅");
    }
    else
    {
        ui->introduce->setText(ans);
        QMessageBox::warning(this,"提示","借阅成功");
    }
}*/
void BorrowBook::on_Return_clicked()
{
    this->close();
}


void BorrowBook::on_find_clicked()
{
    QString target=ui->nameEdit->text();
    bool isFound=false;
    bool isBorrowing=false;
    bor_book newBor;
    for(int i=0;i<bor_books.size();i++)
    {
        if(bor_books[i].name==target)
        {
            QMessageBox::warning(this,"提示","这本书你已经借过了");
            isBorrowing=true;
            break;
        }
    }
    if(!isBorrowing&&bor_books.size()<=3)
    {
        for(int i=0;i<books.size();i++)
        {
            if(books[i].name==target)
            {
                if(!books[i].isBorrowed)
                {
                    ui->introduce->setText(books[i].introduce);
                    QDateTime bor_time=QDateTime::currentDateTimeUtc();
                    newBor.bor_time=bor_time;
                    newBor.name=books[i].name;
                    bor_books.append(newBor);
                    books[i].isBorrowed=true;
                    isFound=true;
                    QMessageBox::warning(this,"提示","预约成功");
                    break;

                }
                if(books[i].isBorrowed)
                {
                    QMessageBox::warning(this,"抱歉","这本书已经被借走");
                    isFound=true;
                    break;
                }
            }
        }
        if(!isFound)
        {
            QMessageBox::warning(this,"抱歉","没找到这本书");
        }
    }
    else if(bor_books.size()>3)
    {
        QMessageBox::warning(this,"提示","借阅数量达到上限");
    }
    for(int i=0;i<bor_books.size();i++)
    {
        switch(i+1)
        {
        case 1:
            ui->name1->setText(bor_books[i].name);
            ui->time1->setText(bor_books[i].bor_time.toString());
            break;
        case 2:
            ui->name2->setText(bor_books[i].name);
            ui->time2->setText(bor_books[i].bor_time.toString());
            break;
        case 3:
            ui->name3->setText(bor_books[i].name);
            ui->time3->setText(bor_books[i].bor_time.toString());
            break;
        }
    }
}



void BorrowBook::on_RTB1_clicked()
{
    QString target=ui->name1->text();
    for(int i=0;i<bor_books.size();i++)
    {
        if(bor_books[i].name==target)
        {
            bor_books.remove(i);
            QMessageBox::warning(this,"提示","归还成功");
            ui->name1->clear();
            ui->time1->clear();
        }
    }
}

void BorrowBook::on_RTB2_clicked()
{
    QString target=ui->name2->text();
    for(int i=0;i<bor_books.size();i++)
    {
        if(bor_books[i].name==target)
        {
            bor_books.remove(i);
            QMessageBox::warning(this,"提示","归还成功");
            ui->name2->clear();
            ui->time2->clear();
        }
    }
}
void BorrowBook::on_RTB3_clicked()
{
    QString target=ui->name3->text();
    for(int i=0;i<bor_books.size();i++)
    {
        if(bor_books[i].name==target)
        {
            bor_books.remove(i);
            QMessageBox::warning(this,"提示","归还成功");
            ui->name3->clear();
            ui->time3->clear();
        }
    }
}
