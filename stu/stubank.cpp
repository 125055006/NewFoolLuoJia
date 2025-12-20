#include "stubank.h"
#include "ui_stubank.h"

StuBank::StuBank(MyClient *client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StuBank)
{
    ui->setupUi(this);
    kr = new BankKr;
    m_client = client;
    money = 0;
    search = new BankSearch(m_client);
    expense = new BankExpense(m_client, money);
    lost = false;

    //展示大量资金
    ui->leftLineEidt->setText(QString::number(money));

    //show hide交互处理
    connect(kr, &BankKr::krHadExit, this, &StuBank::show);
    connect(search, &BankSearch::searchHadExit, this, &StuBank::show);
    connect(expense, &BankExpense::expenseHadExit, this, &StuBank::show);
    //这里收钱
    connect(kr, &BankKr::sendMoney, this, &StuBank::reciveMoney);
    //发出收钱信号，剩下的交给BankSearch对象进行处理
    connect(this, &StuBank::giveOutMoney, search, &BankSearch::writeDowmMoney);
    //给expense发信息
    connect(this, &StuBank::expenseChanged, expense, &BankExpense::monChanged);
    //接收来自BankExpense的扣款信息的connect
    connect(expense, &BankExpense::sendMoneyInfo, [this](const QString &mon) {
        money -= mon.toInt();
        ui->leftLineEidt->setText(QString::number(money));
        emit giveOutMoney("-" + mon);
    });

    this->setWindowTitle("珞珈e卡");
}

StuBank::~StuBank()
{
    delete ui;
}

void StuBank::on_exitButton_clicked()
{
    this->close();
    emit bankHadExit();
}


void StuBank::on_krButton_clicked()
{
    if (!lost) {
        kr->show();
        this->hide();
        return;
    }

    QMessageBox::warning(this, "哒咩", "卡片已挂失，无法使用该功能");
}

//收钱的槽函数
void StuBank::reciveMoney(const QString &mon) {
    money += mon.toInt();
    ui->leftLineEidt->setText(QString::number(money));

    //收完钱后顺手把钱记录到流水上
    emit giveOutMoney("+" + mon);
    //把钱的信息同时传给 expense
    emit expenseChanged(mon);
}

void StuBank::on_searchButton_clicked()
{
    if (!lost) {
        search->show();
        this->hide();
        return;
    }

    QMessageBox::warning(this, "哒咩", "卡片已挂失，无法使用该功能");
}

//卡片挂失处理函数
void StuBank::on_lostButton_clicked()
{
    if (!lost) {
        int ret = QMessageBox::information(this,
                                           "请确认",
                                           "即将挂失卡片，届时所有功能将冻结",
                                           QMessageBox::Yes | QMessageBox::No);

        if (ret == QMessageBox::No) {
            QMessageBox::information(this, "提示", "已放弃挂失");
            qDebug() << "用户已放弃挂失";
            return;
        }

        lost = true;
        ui->lostButton->setText("取消挂失");
        QMessageBox::information(this, "提示", "已成功挂失");
        qDebug() << "用户挂失卡片";
    }

    else {
        int ret = QMessageBox::information(this,
                                           "请确认",
                                           "即将取消挂失卡片，请确定您已取得卡片",
                                           QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::No) {
            QMessageBox::information(this, "提示", "已放弃取消挂失");
            qDebug() << "用户已放弃取消挂失";
            return;
        }

        lost = false;
        ui->lostButton->setText("卡片挂失");
        QMessageBox::information(this, "提示", "已成功取消挂失");
        qDebug() << "用户取消挂失";
    }
}


void StuBank::on_consumeButton_clicked()
{
    expense->show();
    this->hide();
}

