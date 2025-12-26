#include "borrowbook.h"
#include "ui_borrowbook.h"
BorrowBook::BorrowBook(MyClient *client,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BorrowBook)
    ,m_client(client)
{
    ui->setupUi(this);
    loadBooks();
    connect(m_client,&MyClient::SendBookInfo,this,&BorrowBook::UpdataBooks);
}

BorrowBook::~BorrowBook()
{
    delete ui;
}

void BorrowBook::loadBooks()
{
    QString path="F:\\Qt\\NewFoolLuoJia1\\tea\\books.txt";
    QFile file(path);
    if(!file.exists())
    {
        QMessageBox::warning(this,"错误","找不到书籍数据"+file.errorString());
        return;
    }
    if(!file.open(QIODevice::ReadOnly|QIODevice::WriteOnly))
    {
        QMessageBox::warning(this,"错误","读取书籍信息失败");
    }
    QTextStream in(&file);
    books.clear();
    while(!in.atEnd())
    {
        QString line=in.readLine();
        QStringList parts=line.split(" ");
        book temp;
        temp.name=parts[0];
        temp.introduce=parts[1];
        temp.isBorrowed=(parts[2]=="true");
        books.append(temp);
    }
    file.close();
    QString tip="成功读取";
    tip+=QString::number(books.size());
    tip+=+"本书";
    QMessageBox::warning(this,"提示",tip);
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
                    QString path="F:\\Qt\\NewFoolLuoJia1\\tea\\books.txt";
                    QFile file(path);
                    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
                    {
                        QMessageBox::warning(this,"错误","更新书籍状态错误");
                        return;
                    }
                    QTextStream out(&file);
                    for(auto &temp:books)
                    {
                        out<<temp.name<<" "<<temp.introduce<<" "<<(temp.isBorrowed?"true":"false")<<"\n";
                    }
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
    for(auto& temp:books)
    {
        if(temp.name==target)
        {
            temp.isBorrowed=false;
            QString path="F:\\Qt\\NewFoolLuoJia1\\tea\\books.txt";
            QFile file(path);
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                QMessageBox::warning(this,"错误","更新书籍状态错误");
                return;
            }
            QTextStream out(&file);
            for(auto &temp:books)
            {
                out<<temp.name<<" "<<temp.introduce<<" "<<(temp.isBorrowed?"true":"false")<<"\n";
            }
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
    for(auto& temp:books)
    {
        if(temp.name==target)
        {
            temp.isBorrowed=false;
            QString path="F:\\Qt\\NewFoolLuoJia1\\tea\\books.txt";
            QFile file(path);
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                QMessageBox::warning(this,"错误","更新书籍状态错误");
                return;
            }
            QTextStream out(&file);
            for(auto &temp:books)
            {
                out<<temp.name<<" "<<temp.introduce<<" "<<(temp.isBorrowed?"true":"false")<<"\n";
            }
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
    for(auto& temp:books)
    {
        if(temp.name==target)
        {
            temp.isBorrowed=false;
            QString path="F:\\Qt\\NewFoolLuoJia1\\tea\\books.txt";
            QFile file(path);
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                QMessageBox::warning(this,"错误","更新书籍状态错误");
                return;
            }
            QTextStream out(&file);
            for(auto &temp:books)
            {
                out<<temp.name<<" "<<temp.introduce<<" "<<(temp.isBorrowed?"true":"false")<<"\n";
            }
        }
    }
}
