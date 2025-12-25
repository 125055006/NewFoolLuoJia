#include "dormdistribute.h"
#include "ui_dormdistribute.h"

DormDistribute::DormDistribute(MyServer *server, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DormDistribute)
{
    ui->setupUi(this);
    m_server = server;

    ui->nameLineEdit->setPlaceholderText("等待学生注册...");
    ui->chooseComboBox->setPlaceholderText("请选择分配的寝室");
    ui->chooseComboBox->addItems({"桂园", "樱园", "竹园", "梅园", "松园"});
    ui->chooseComboBox->setCurrentText("");

    //一开始让与更换寝室有关的控件hide
    ui->reasonLabel->hide();
    ui->reasonLineEdit->hide();
    ui->obeyLabel->hide();
    ui->obeyLineEdit->hide();
    ui->rufuseButton->hide();
    //当然要锁上reason和obey  refuseButton只有当收到exchange信号时才释放
    ui->reasonLineEdit->setReadOnly(true);
    ui->obeyLineEdit->setReadOnly(true);
    ui->rufuseButton->setEnabled(false);

    //逐级从Record获取学生的姓名 最终由这个connect输入至LineEdit
    connect(this, &DormDistribute::getName, this, &DormDistribute::onNameGet);
    //这个connect用来处理 接收到更换申请信息 后的操作
    connect(m_server, &MyServer::reciveExchange, this, &DormDistribute::reciveExchange);

    this->setWindowTitle("恭喜您中奖了");
}

DormDistribute::~DormDistribute()
{
    delete ui;
}

void DormDistribute::on_exitButton_clicked()
{
    this->close();
    emit distriHadExit();
}

void DormDistribute::onNameGet(const QString &name) {
    ui->nameLineEdit->setText(name);
}

void DormDistribute::on_commitButton_clicked()
{
    QString name = ui->nameLineEdit->text();
    QString choose = ui->chooseComboBox->currentText();

    if (name.isEmpty() || choose.isEmpty()) {
        QMessageBox::warning(this, "警告", "学生未注册或宿舍未选择");
        qDebug() << "分配任务失败";
        return;
    }

    m_server->sendToAllClients("宿舍分配" + choose);
    QMessageBox::information(this, "ok!", "成功分配");
    qDebug() << "成功发送";

    //把确认键锁上 防止用户没事乱按
    ui->commitButton->setEnabled(false);
    ui->commitButton->setText("已确认");
}

void DormDistribute::reciveExchange(const QString &Info) {
    //丢一个QMessageBox提示用户
    QMessageBox::information(this, "你好", "有新的更换请求");

    //解锁commitButton refuseButton
    ui->commitButton->setEnabled(true);
    ui->commitButton->setText("确认");
    ui->rufuseButton->setEnabled(true);

    //让隐身的控件现形
    ui->reasonLabel->show();
    ui->reasonLineEdit->show();
    ui->obeyLabel->show();
    ui->obeyLineEdit->show();
    ui->rufuseButton->show();

    //Info格式为1./2./3.读取其内部的信息   类似于Record中的QStringList方法
    QStringList part = Info.split("/");

    //这里选择重新初始化一下chooseComboBox
    ui->chooseComboBox->clear();
    ui->chooseComboBox->setPlaceholderText("请选择调整后的宿舍");
    ui->chooseComboBox->addItems({"桂园", "樱园", "竹园", "梅园", "松园"});
    ui->chooseComboBox->setCurrentText("");

    ui->reasonLineEdit->setText(part[0] + ";" + part[1]);
    ui->obeyLineEdit->setText(part[2]);
}

//学生申请更换宿舍惨遭拒绝
void DormDistribute::on_rufuseButton_clicked()
{
    int ret = QMessageBox::warning(this,
                         "真的要这么做吗？",
                         "这样" + ui->nameLineEdit->text() + "会伤心的",
                                   QMessageBox::Yes | QMessageBox::No);

    if (ret == QMessageBox::Yes) {
        m_server->sendToAllClients("拒绝更换");
        qDebug() << "已拒绝" << ui->nameLineEdit->text() << "的更换请求";

        //如果确认无误 锁上确认键和拒绝键
        ui->commitButton->setEnabled(false);
        ui->rufuseButton->setEnabled(false);
        ui->rufuseButton->setText("已无情拒绝");
    }
}

