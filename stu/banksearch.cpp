#include "banksearch.h"
#include "ui_banksearch.h"

BankSearch::BankSearch(MyClient *client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BankSearch)
{
    ui->setupUi(this);

    //这里是把信号最终传递到槽函数的实现
    connect(this, &BankSearch::writeDowmMoney, this, &BankSearch::toWriteDown);

    this->setWindowTitle("平账现场");
}

BankSearch::~BankSearch()
{
    delete ui;
}

void BankSearch::on_exitButton_clicked()
{
    this->close();
    emit searchHadExit();
}

void BankSearch::toWriteDown(const QString &mon) {
    //读取第一个字符，先看他是正还是负
    bool getOrlose;
    QString info = mon.mid(1);
    if (mon.startsWith("+")) {
        getOrlose = true;
    }
    else {
        getOrlose = false;
    }
    //首先获取目前的时间 转化为字符串格式
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString DateTimeStr = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");  //时间的格式化输出

    QString note = DateTimeStr + "  " + (getOrlose ? "通过卡片充值，充值了" : "通过生活缴费，开销了") + info + "元";

    //下面把数据输入TextEdit
    //先检查TextEdit是否为空，若为空则直接输入
    if (ui->searchTextEdit->toPlainText().isEmpty()) {
        ui->searchTextEdit->insertPlainText(note);
        qDebug() << "已记录：" << (getOrlose ? "充值 " : "开销 ") << info << "元";
        return;
    }

    //再处理不为空，新的输入应当在最上
    //获取光标位置，将其设置到TextEdit的最前
    QTextCursor cursor = ui->searchTextEdit->textCursor();
    cursor.movePosition(QTextCursor::Start);

    //输入
    cursor.insertText(note + "\n");
    qDebug() << "已记录：" << (getOrlose ? "充值 " : "开销 ") << info << "元";
}
