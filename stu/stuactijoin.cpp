#include "stuactijoin.h"
#include "ui_stuactijoin.h"

StuActiJoin::StuActiJoin(MyClient *client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StuActiJoin)
{
    ui->setupUi(this);
    m_client = client;
    count = 0;

    for (int i = 1; i < 5; i++) {
        QString Obj1 = QString("actLineEdit%1").arg(i);
        QString Obj2 = QString("joinButton%1").arg(i);

        //通过有序命名访问控件
        QLineEdit *edit = findChild<QLineEdit*>(Obj1);
        QPushButton *button = findChild<QPushButton*>(Obj2);

        if (edit && button) {
            button->setEnabled(false);

            to_connect_two[edit] = button;

            //绑定单击信号与槽函数
            connect(button, &QPushButton::clicked, this, &StuActiJoin::toJoinActi);
        }
    }

    connect(m_client, &MyClient::SendJoinInfo, this, &StuActiJoin::newJoin);

    this->setWindowTitle("参加活动");
}

StuActiJoin::~StuActiJoin()
{
    delete ui;
}

void StuActiJoin::on_exitButton_clicked()
{
    this->close();
    emit joinExit();
}

void StuActiJoin::newJoin(const QString &join_Info) {
    count++;

    QString Obj = QString("actLineEdit%1").arg(count);
    QLineEdit *edit = findChild<QLineEdit*>(Obj);

    edit->setText(join_Info);
    to_connect_two[edit]->setEnabled(!join_Info.isEmpty());
}

void StuActiJoin::toJoinActi() {
    //这里需要向服务器发送一些信号和数据  晚点再回来补
    QString Info("成功参加");
    m_client->sendMessage(Info);

    QMessageBox::information(this, "冷知识", "参加成功");
    QPushButton *button = qobject_cast<QPushButton*>(sender());

    if (button) {
        button->setText("已参加");
        button->setEnabled(false);
    }

    else {
        qDebug() << "出现错误！";
    }
}
