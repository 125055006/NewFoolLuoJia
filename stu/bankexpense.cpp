#include "bankexpense.h"
#include "ui_bankexpense.h"

BankExpense::BankExpense(MyClient *client,int mon, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BankExpense)
{
    ui->setupUi(this);
    m_client = client;
    isThisMonth = false;
    isThisYear = false;
    money = mon;

    //第一次缴费 必须等教师端发布学宿费后才能实现
    ui->commitButton->setEnabled(false);

    //接收重置信号的connect
    connect(m_client, &MyClient::getReInfo, [this]() {
        isThisMonth = false;
        QMessageBox::information(this, "喂喂", "杂鱼，生活缴费重置了");
    });
    //设置money的connect
    connect(this, &BankExpense::monChanged, [this](const QString &mon) {
        money += mon.toInt();
    });
    //这个连接接收来自教师端的信息
    connect(m_client, &MyClient::getFeeInfo, [this](const QString &info) {
        QStringList part = info.split("/");
        ui->learnFeeLineEdit->setText(part[0]);
        ui->residenceLineEdit->setText(part[1]);
        //这个时候解锁commitButton
        ui->commitButton->setEnabled(true);
    });
}

BankExpense::~BankExpense()
{
    delete ui;
}

void BankExpense::on_exitButton_clicked()
{
    this->close();
    emit expenseHadExit();
}


void BankExpense::on_commitButton_clicked()
{
    //这个函数的逻辑是 由成员确定这个月是否已缴纳水、电、网费，这个成员接收教师端的信号来更新
    //学费、住宿费由教师端来设置，但只能设置一次（毕竟这个东西交的频率确实不高） 最后汇总一起在StuBank中的余额中扣除
    if (!isThisMonth) {
        //先把生活费读了先
        QString ele = ui->electricityLineEdit->text();
        QString water = ui->waterLineEdit->text();
        QString net = ui->netLineEdit->text();
        //这里创建QString对象可以提高代码复用性
        QString learn;
        QString residence;

        if (!isThisYear) {
            learn = ui->learnFeeLineEdit->text();
            residence = ui->residenceLineEdit->text();
        }

        //计算费用 与存款进行有个比较
        int fee = ele.toInt() + water.toInt() + net.toInt() + learn.toInt() + residence.toInt();

        if (fee > money) {
            QMessageBox::warning(this, "不行噢", "余额不足，充值失败");
            qDebug() << "需" << fee << " " << "余额" << money << " " << "充值失败";
            return;
        }

        int ret = QMessageBox::information(this,
                                           "请确认交易",
                                           "充值：" + QString::number(fee) + "可以吗？",
                                           QMessageBox::Yes | QMessageBox::No);

        if (ret == QMessageBox::No) {
            QMessageBox::information(this, "好的", "已取消充值");
            qDebug() << "用户取消充值";
            return;
        }

        QMessageBox::information(this, "ok!", "已成功充值");
        qDebug() << "成功充值" << fee << "元费用";

        //如果未交学费 就设置学费的状态
        if (!isThisYear) {
            isThisYear = true;
            //教师端的学宿费ComboBox
            m_client->sendMessage("全部缴纳");
        }
        else {
             m_client->sendMessage("水电网费已交");
        }

        isThisMonth = true;
        money -= fee; //重新设定money
        //发送信号
        emit sendMoneyInfo(QString::number(fee));
        //教师端的生活费
        return;
    }

    //这里是缴费已结清的分支
    QMessageBox::warning(this, "?", "？结清了还想交");
    return;
}

