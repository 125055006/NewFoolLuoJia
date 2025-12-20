#include "dormexchange.h"
#include "ui_dormexchange.h"

DormExchange::DormExchange(MyClient *client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DormExchange)
{
    ui->setupUi(this);
    m_client = client;

    ui->optionLineEdit->hide();
    //设置给出的选项
    //ui->optionComboBox->setEditable(true);
    ui->optionComboBox->setPlaceholderText("请选择您申请原因...");
    ui->optionComboBox->addItems({"舍友不和", "环境不适", "玩原神", "其他"});
    ui->optionComboBox->setCurrentText("");

    //读取用户自己输入的选项
    //QStringList customOption = getCustomOptions();   不符合实现的逻辑

    ui->exchangeComboBox->setPlaceholderText("选择您想更换到的宿舍");
    ui->exchangeComboBox->addItems({"桂园", "樱园", "竹园", "梅园", "松园"});
    ui->exchangeComboBox->setCurrentText("");

    connect(ui->optionComboBox, &QComboBox::currentTextChanged, this, &DormExchange::onOtherOptionChosed);

    this->setWindowTitle("为什么要换宿舍啊！！！");
}

DormExchange::~DormExchange()
{
    delete ui;
}

void DormExchange::on_exitButton_clicked()
{
    this->close();
    emit exchangeHadExit();
}

//这里准备上设置一个可选择的几个选项
//1 2 3 4 5...最后设置一个其他类，供用户自己输入需要调整寝室的理由
//看来需要处理这样一个技术性问题

void DormExchange::onOtherOptionChosed() {
    if (ui->optionComboBox->currentText() != "其他") {
        ui->optionLineEdit->clear();
        ui->optionLineEdit->hide();
        return;
    }

    ui->optionLineEdit->setPlaceholderText("请输入您的理由...");
    ui->optionLineEdit->show();
}

void DormExchange::on_commitBotton_clicked()
{
    QString reason = ui->optionComboBox->currentText();
    if (reason == "其他") {
        reason = ui->optionLineEdit->text();

        if (reason.isEmpty()) {
            QMessageBox::warning(this, "不需要理由~", "你理由还没填呢");
            return;
        }
    }
    QString opt = ui->exchangeComboBox->currentText();
    if (opt.isEmpty()) {
        QMessageBox::warning(this, "你要去哪", "未选择调整后宿舍");
    }
    QString adjust = QString(ui->checkBox->isChecked() ? "学生服从调剂" : "学生不服从调剂");

    QString info = QString("%1/%2/%3").arg(reason).arg(opt).arg(adjust);
    m_client->sendMessage("更换申请" + info);

    QMessageBox::information(this, "好耶", "已成功提交申请");
}

