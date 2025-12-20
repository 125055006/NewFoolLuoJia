#include "dormfix.h"
#include "ui_dormfix.h"

DormFix::DormFix(MyClient *client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DormFix)
{
    ui->setupUi(this);
    m_client = client;

    ui->reasonComboBox->setPlaceholderText("请选择报修类型");
    ui->reasonComboBox->addItems({"门窗", "空调", "床铺", "电力"});
    ui->reasonComboBox->setCurrentText("");

    this->setWindowTitle("让师傅看看怎么个事");
}

DormFix::~DormFix()
{
    delete ui;
}

void DormFix::on_exitButton_clicked()
{
    this->close();
    emit fixHadExit();
}


void DormFix::on_commitButton_clicked()
{
    QString reason = ui->reasonComboBox->currentText();
    QString detail = ui->detailLineEdit->text();

    if (reason.isEmpty() || detail.isEmpty()) {
        QMessageBox::warning(this, "oi", "你要输入完整的理由");
        qDebug() << "输入的理由存在问题";
        return;
    }

    QString isNeed = ui->checkBox->isChecked() ? "紧急" : "非紧急";

    QString info = QString("1%/2%/3%").arg(reason).arg(detail).arg(isNeed);

    m_client->sendMessage(info);
}

