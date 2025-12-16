#include "CampusFeedback.h"
#include "ui_CampusFeedback.h"

CampusFeedback::CampusFeedback(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CampusFeedback)
{
    ui->setupUi(this);

    // 设置窗口标题
    this->setWindowTitle("校园意见反馈系统");
    // 初始化下拉框选项
    ui->cbxType->addItems({"设施问题", "教学问题", "管理问题", "其他建议"});
    // 加载本地已保存的反馈数据
    loadFeedbackData();

}

CampusFeedback::~CampusFeedback()
{
    delete ui;
}

// 提交反馈按钮点击事件
void CampusFeedback::on_btnAdd_clicked()
{
    // 1. 获取输入内容
    QString type = ui->cbxType->currentText();
    QString title = ui->leTitle->text().trimmed();
    QString content = ui->teContent->toPlainText().trimmed();

    // 2. 输入验证
    if (title.isEmpty())
    {
        QMessageBox::warning(this, "输入错误", "反馈标题不能为空！");
        ui->leTitle->setFocus();
        return;
    }
    if (content.isEmpty())
    {
        QMessageBox::warning(this, "输入错误", "详细内容不能为空！");
        ui->teContent->setFocus();
        return;
    }

    // 3. 保存反馈数据
    if (saveFeedback(type, title, content))
    {
        // 4. 添加到列表显示
        QString feedbackItem = QString("[%1] %2 - %3").arg(type).arg(title).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm"));
        ui->lwFeedbackList->addItem(feedbackItem);

        // 5. 提示成功并清空输入
        QMessageBox::information(this, "提交成功", "您的反馈已提交，感谢您的建议！");
        on_btnClear_clicked(); // 复用清空函数
    }
    else
    {
        QMessageBox::critical(this, "保存失败", "反馈提交失败，请检查文件权限！");
    }
}

// 清空输入按钮点击事件
void CampusFeedback::on_btnClear_clicked()
{
    ui->leTitle->clear();
    ui->teContent->clear();
    ui->cbxType->setCurrentIndex(0); // 重置为第一个选项
    ui->leTitle->setFocus(); // 焦点回到标题输入框
}

// 加载本地反馈数据
void CampusFeedback::loadFeedbackData()
{
    QFile file("feedback.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return; // 文件不存在则直接返回

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty())
        {
            ui->lwFeedbackList->addItem(line);
        }
    }
    file.close();
}

// 保存新反馈到本地文件
bool CampusFeedback::saveFeedback(const QString &type, const QString &title, const QString &content)
{
    QFile file("feedback.txt");
    if (!file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    // 按行存储：时间|类型|标题|内容
    QString feedbackLine = QString("%1|%2|%3|%4\n")
                               .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
                               .arg(type)
                               .arg(title)
                               .arg(content);
    out << feedbackLine;

    file.close();
    return true;
}
