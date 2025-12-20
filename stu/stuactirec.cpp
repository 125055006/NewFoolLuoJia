#include "stuactirec.h"
#include "ui_stuactirec.h"

StuActiRec::StuActiRec(MyClient *client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StuActiRec)
{
    ui->setupUi(this);
    m_client = client;
    count = 0;
    ui->finishLineEdit->setText(QString::number(count));

    connect(m_client, &MyClient::SendClubInfo, this, &StuActiRec::displayInfo);
}

StuActiRec::~StuActiRec()
{
    delete ui;
}

void StuActiRec::displayInfo(const QString &ClubInfo)
{
    if (count == 4) {
        m_client->sendMessage("学生社团活动已完成");

        qDebug() << "已完成所有活动";
        return;
    }

    count++;

    QString Obj = QString("recLineEdit%1").arg(count);
    QLineEdit *edit = findChild<QLineEdit*>(Obj);

    //判断edit是否存在
    if (edit) {
        edit->setText(ClubInfo);
        ui->finishLineEdit->setText(QString::number(count));
    }
    else {
        qDebug() << "未找到对象，处理出错 " << Obj;
        count--;
    }
}

void StuActiRec::on_exitButton_clicked()
{
    this->close();
    emit recExit();
}

