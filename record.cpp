#include "record.h"
#include "ui_record.h"

Record::Record(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Record)
{
    ui->setupUi(this);

}
Record::~Record()
{
    delete ui;
}

void Record::on_Save_clicked()
{
    QLineEdit *idEdit=ui->idEdit;
    QString id=idEdit->text();
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
    QString address=addressEdit->text();
    QString info=QString("%1|%2|%3|%4|%5|%6|%7|%8")
                       .arg(id).arg(name).arg(sex).arg(age).arg(major).arg(Class).arg(phone).arg(address);
}

