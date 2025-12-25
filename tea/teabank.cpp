#include "teabank.h"
#include "ui_teabank.h"

TeaBank::TeaBank(MyServer *server, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TeaBank)
{
    ui->setupUi(this);
    m_server = server;

    //将CheckBox设置为只读
    ui->lifeFeeCheckBox->setEnabled(false);
    ui->learn_residenceCheckBox->setEnabled(false);
    //默认初始学生没有充值水电网费，那么重置按钮应该禁用
    ui->reButton->setEnabled(false);

    //连接对CheckBox的改变信号
    connect(m_server, &MyServer::getLearn_Residence, [this]() {
        ui->learn_residenceCheckBox->setChecked(true);
        ui->lifeFeeCheckBox->setChecked(true);
        ui->reButton->setEnabled(true);
    });
    connect(m_server, &MyServer::getLifeFee, [this]() {
        ui->lifeFeeCheckBox->setChecked(true);
        ui->reButton->setEnabled(true);
    });

    this->setWindowTitle("开始剥削");
}

TeaBank::~TeaBank()
{
    delete ui;
}

void TeaBank::on_exitButton_clicked()
{
    this->close();
    emit bankHadExit();
}


void TeaBank::on_commitButton_clicked()
{
    QString learn = ui->learnFeeLineEdit->text();
    QString residence = ui->residenceLineEdit->text();

    if (learn.isEmpty() || residence.isEmpty()) {
        QMessageBox::warning(this, "？", "请输入金额");
        qDebug() << "未输入金额";
        return;
    }

    if (learn.toInt() < 0 || residence.toInt() < 0) {
        QMessageBox::warning(this, "？", "不要倒贴钱");
        qDebug() << "学费或住宿费为负";
        return;
    }

    m_server->sendToAllClients("学宿费发布" + learn + "/" + residence);
    QMessageBox::information(this, "ok!", "成功发布");
    qDebug() << "成功发布";

    //成功发布之后 LineEdit应处于只读状态
    ui->learnFeeLineEdit->isReadOnly();
    ui->residenceLineEdit->isReadOnly();

    //在程序运行时只会提交一次学宿费 所以当这个槽函数运行完 直接把Button锁死就好
    ui->commitButton->setEnabled(false);
    ui->commitButton->setText("已发布");
}


void TeaBank::on_reButton_clicked()
{
    int ret = QMessageBox::information(this,
                                       "确认",
                                       "确定要重置水电网费吗？",
                                       QMessageBox::Yes | QMessageBox::No);

    if (ret == QMessageBox::No) {
        QMessageBox::information(this, "嗯哼", "已成功取消重置");
        qDebug() << "取消重置";
        return;
    }

    QMessageBox::information(this, "ok!", "已重置");
    qDebug() << "重置成功";
    ui->lifeFeeCheckBox->setChecked(false);

    m_server->sendToAllClients("水电重置");
    //这时候把Button锁住
    ui->reButton->setEnabled(false);
}

