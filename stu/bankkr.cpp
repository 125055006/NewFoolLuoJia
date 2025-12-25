#include "bankkr.h"
#include "ui_bankkr.h"

BankKr::BankKr(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BankKr)
{
    ui->setupUi(this);

    //对krComboBox进行处理
    ui->krComboBox->setPlaceholderText("请选择要充值的金额（元）...");
    ui->krComboBox->addItems({"10", "50", "100", "200", "自定义金额"});
    ui->krComboBox->setCurrentText("");
    //隐藏自定义金额的LineEdit
    ui->krLineEdit->hide();

    //连接信号与槽 实现krComboBox选择到自定义对LineEdit的显示
    connect(ui->krComboBox, &QComboBox::currentTextChanged, this, &BankKr::krComboBoxChanged);
}

BankKr::~BankKr()
{
    delete ui;
}

void BankKr::on_exitButton_clicked()
{
    this->close();
    emit krHadExit();
}

void BankKr::krComboBoxChanged() {
    QString select = ui->krComboBox->currentText();
    if (select != "自定义金额") {
        //清空记录，隐藏
        ui->krLineEdit->hide();
        ui->krLineEdit->clear();
        return;
    }

    ui->krLineEdit->show();
}

void BankKr::on_commitButton_clicked()
{
    //读取ComboBox和LineEdit中的数据
    QString kr1 = ui->krComboBox->currentText();

    //未选择krComboBox的情况
    if (kr1.isEmpty()) {
        QMessageBox::warning(this, "充钱在呢", "到底充多少");
        qDebug() << "输入金额为空";
        return;
    }

    //选择了指定金额进入代码
    if (kr1 != "自定义金额") {
        int select = QMessageBox::information(this,
                                 "只差最后一步了",
                                 "充值" + kr1 + "这样可以吗？",
                                 QMessageBox::Yes | QMessageBox::No);
        if (select == QMessageBox::Yes) {
            QMessageBox::information(this, "ok!", "充值成功");
            qDebug() << "已成功充值" << kr1 << "金额";
            emit sendMoney(kr1);
            return;
        }
        else {
            QMessageBox::information(this, "好的", "充值已取消");
            qDebug() << "用户已取消充值操作";
            return;
        }
    }

    //此时kr1为自定义 读取LineEdit的数据进行进一步分析
    QString kr2 = ui->krLineEdit->text();

    //kr2为空
    if (kr2.isEmpty()) {
        QMessageBox::warning(this, "充钱在呢", "怎么还不输入金额");
        qDebug() << "输入金额为空";
        return;
    }

    //kr2为负数
    if (kr2.toInt() < 0) {
        QMessageBox::warning(this, "搞什么？", "不要充负数口牙");
        qDebug() << "用户试图充负数";
        return;
    }

    //这里终于充正确了
    int select = QMessageBox::information(this,
                                          "只差最后一步了",
                                          "充值" + kr2 + "这样可以吗？",
                                          QMessageBox::Yes | QMessageBox::No);
    if (select == QMessageBox::Yes) {
        QMessageBox::information(this, "ok!", "充值成功");
        qDebug() << "已成功充值" << kr2 << "金额";
        emit sendMoney(kr2);
        return;
    }
    else {
        QMessageBox::information(this, "好的", "充值已取消");
        qDebug() << "用户已取消充值操作";
        return;
    }
}

