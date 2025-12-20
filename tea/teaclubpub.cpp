#include "teaclubpub.h"
#include "ui_teaclubpub.h"

TeaClubPub::TeaClubPub(MyServer *server, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TeaClubPub)
{
    ui->setupUi(this);
    m_server = server;

    for (int i = 1 ; i < 5; i++) {
        QString Obj1 = QString("pubButton%1").arg(i);
        QString Obj2 = QString("pubLineEdit%1").arg(i);

        QPushButton *button = findChild<QPushButton*>(Obj1);
        QLineEdit *edit = findChild<QLineEdit*>(Obj2);

        to_connect[button] = edit;

        connect(button, &QPushButton::clicked, this, &TeaClubPub::toPublish);
    }

    this->setWindowTitle("发布活动吧~");

    connect(this, &TeaClubPub::sendClubActi, m_server, &MyServer::sendToAllClients);
}

TeaClubPub::~TeaClubPub()
{
    delete ui;
}

void TeaClubPub::on_exitButton_clicked()
{
    this->close();
    emit pubHadExit();
}

void TeaClubPub::toPublish() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());

    if (to_connect[button]->text().isEmpty()) {
        QMessageBox::warning(this, "补兑", "未输入活动内容");
        return;
    }

    else {
        QString info = "社团活动" + to_connect[button]->text();
        emit sendClubActi(info);
        emit needCommit(to_connect[button]->text());
        QMessageBox::information(this, "好耶", "活动发布成功");
        qDebug() << "活动已发布";
    }
}
