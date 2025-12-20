#include "teaclubcomi.h"
#include "ui_teaclubcomi.h"

TeaClubComi::TeaClubComi(MyServer *server, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TeaClubComi)
{
    ui->setupUi(this);
    m_server = server;
    count = 0;

    for (int i = 1; i < 5; i++) {
        QString Obj1 = QString("actLineEdit%1").arg(i);
        QString Obj2 = QString("commitButton%1").arg(i);

        QLineEdit *edit = findChild<QLineEdit*>(Obj1);
        QPushButton *button = findChild<QPushButton*>(Obj2);

        button->setEnabled(false);

        to_connect[edit] = button;
        connect(button, &QPushButton::clicked, this, &TeaClubComi::finishActi);
    }

    connect(this, &TeaClubComi::toDoNew, this, &TeaClubComi::newActi);
    connect(m_server, &MyServer::stuReadyJoin, this, &TeaClubComi::isJoin);
    this->setWindowTitle("活动签到");
}

TeaClubComi::~TeaClubComi()
{
    delete ui;
}

void TeaClubComi::on_exitButton_clicked()
{
    this->close();
    emit comiHadExit();
}

void TeaClubComi::newActi(const QString &Info) {
    if (Info.isEmpty()) {
        return;
    }

    count++;

    QString Obj = QString("actLineEdit%1").arg(count);
    QLineEdit *edit = findChild<QLineEdit*>(Obj);

    edit->setText(Info);
    to_connect[edit]->setEnabled(true);
}

void TeaClubComi::finishActi() {
    if (!join) {
        QMessageBox::warning(this, "oi", "学生还未参加!");
        qDebug() << "等待学生参加";
        return;
    }

    QMessageBox::information(this, "芜湖", "已确认社团活动完成");

    QString Obj = QString("actLineEdit%1").arg(count);
    QLineEdit *edit = findChild<QLineEdit*>(Obj);

    QString Club_Info = "社团活动记录" + edit->text();
    m_server->sendToAllClients(Club_Info);

    to_connect[edit]->setEnabled(false);
    to_connect[edit]->setText("已确认签到");

    //重置join的状态
    join = false;
}

void TeaClubComi::isJoin() {
    join = true;
}
