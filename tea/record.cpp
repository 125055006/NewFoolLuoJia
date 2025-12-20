#include "record.h"
#include "ui_record.h"

Record::Record(MyServer *server,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Record)
    ,server(server)
{

    ui->setupUi(this);
    //connect(server,&MyServer::GetStuInfo,this,&Record::onGetStuInfo);
}
Record::~Record()
{
    delete ui;
}

//void Record::onGetStuInfo(const QString &info)
//{
//    qDebug()<<"收到学生信息："<<info;
//}
void Record::on_Save_clicked()
{
    isRepeated=false;
    QLineEdit *idEdit=ui->idEdit;
    QString id=idEdit->text();
    for(int i=0;i<idHouse.size();i++)
    {
        if(id==idHouse[i])
        {
            QMessageBox::warning(this,"警告","学号重复");
            isRepeated=true;
            ui->idEdit->clear();
        }
    }
    idHouse.append(id);
    QLineEdit *nameEdit=ui->nameEdit;
    QString name=nameEdit->text();
    QLineEdit *sexEdit=ui->sexEdit;
    QString sex=sexEdit->text();
    QLineEdit *ageEdit=ui->ageEdit;
    QString age=ageEdit->text();
    QLineEdit *majorEdit=ui->majorEdit;
    QString major=majorEdit->text();
    QLineEdit *classEdit=ui->classEdit;
    QString Class=classEdit->text();
    QLineEdit *phoneEdit=ui->phoneEdit;
    QString phone=phoneEdit->text();
    QLineEdit *addressEdit=ui->addressEdit;
    QString address=addressEdit->text();    //发送信息
    QString info=QString("%1/%2/%3/%4/%5/%6/%7/%8")
                       .arg(id).arg(name).arg(sex).arg(age)
                       .arg(major).arg(Class).arg(phone).arg(address);
    QStringList part=info.split('/');
    if(!isRepeated)
    {
        server->sendToAllClients("学生信息"+info);
        qDebug()<<"信息已发送";
        emit sendStuInfo(info);
        emit sendToDorm(name);
    }
}


void Record::on_Cancel_clicked()
{
    this->close();
}

