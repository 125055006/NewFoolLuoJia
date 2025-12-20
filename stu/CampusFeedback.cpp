#include "CampusFeedback.h"
#include "ui_CampusFeedback.h"
#include<QMenu>
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

// 提交反馈（原有逻辑不变）
void CampusFeedback::on_btnAdd_clicked()
{
    QString type = ui->cbxType->currentText();
    QString title = ui->leTitle->text().trimmed();
    QString content = ui->teContent->toPlainText().trimmed();

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

    if (saveFeedback(type, title, content))
    {
        QString feedbackItem = QString("[%1] %2 - %3").arg(type).arg(title).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm"));
        ui->lwFeedbackList->addItem(feedbackItem);
        QMessageBox::information(this, "提交成功", "您的反馈已提交，感谢您的建议！");
        on_btnClear_clicked();
    }
    else
    {
        QMessageBox::critical(this, "保存失败", "反馈提交失败，请检查文件权限！");
    }
}

// 清空输入（原有逻辑不变）
void CampusFeedback::on_btnClear_clicked()
{
    ui->leTitle->clear();
    ui->teContent->clear();
    ui->cbxType->setCurrentIndex(0);
    ui->leTitle->setFocus();
}

// 新增：删除选中反馈
void CampusFeedback::on_btnDelete_clicked()
{
    // 1. 获取选中的列表项
    QListWidgetItem *selectedItem = ui->lwFeedbackList->currentItem();
    if (!selectedItem)
    {
        QMessageBox::warning(this, "删除失败", "请先选中要删除的反馈！");
        return;
    }

    // 2. 确认删除
    int ret = QMessageBox::question(this, "确认删除", "是否确定删除选中的反馈？删除后不可恢复！",
                                    QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret != QMessageBox::Yes)
        return;

    // 3. 删除列表项并同步删除文件中的记录
    QString itemText = selectedItem->text();
    if (deleteFeedback(itemText))
    {
        // 4. 从列表中移除项
        delete selectedItem; // 释放内存
        QMessageBox::information(this, "删除成功", "选中的反馈已删除！");
    }
    else
    {
        QMessageBox::critical(this, "删除失败", "文件操作失败，无法删除反馈记录！");
    }
}

// 加载反馈数据（原有逻辑不变）
void CampusFeedback::loadFeedbackData()
{
    QFile file("feedback.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty())
        {
            // 解析文件行，生成列表项文本
            QStringList parts = line.split("|");
            if (parts.size() >= 4)
            {
                QString type = parts[1];
                QString title = parts[2];
                QString time = parts[0].left(16).replace("T", " "); // 适配时间格式
                QString listItem = QString("[%1] %2 - %3").arg(type).arg(title).arg(time);
                ui->lwFeedbackList->addItem(listItem);
            }
        }
    }
    file.close();
}

// 保存反馈（原有逻辑不变）
bool CampusFeedback::saveFeedback(const QString &type, const QString &title, const QString &content)
{
    QFile file("feedback.txt");
    if (!file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    QString feedbackLine = QString("%1|%2|%3|%4\n")
                               .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
                               .arg(type)
                               .arg(title)
                               .arg(content);
    out << feedbackLine;

    file.close();
    return true;
}

// 新增：删除指定反馈记录
bool CampusFeedback::deleteFeedback(const QString &itemText)
{
    // 1. 解析列表项文本，提取关键信息（类型+标题+时间）
    QStringList itemParts = itemText.split(" - ");
    if (itemParts.size() < 2)
        return false;

    QString typeTitle = itemParts[0].mid(1, itemParts[0].length()-1); // 去掉[
    QString time = itemParts[1];
    QStringList typeTitleParts = typeTitle.split("] ");
    if (typeTitleParts.size() < 2)
        return false;

    QString type = typeTitleParts[0];
    QString title = typeTitleParts[1];

    // 2. 读取文件所有行，过滤掉要删除的记录
    QFile file("feedback.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QList<QString> keepLines;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        QStringList lineParts = line.split("|");
        // 匹配时间（前16位）、类型、标题
        if (lineParts.size() >= 4)
        {
            QString lineTime = lineParts[0].left(16).replace("T", " ");
            QString lineType = lineParts[1];
            QString lineTitle = lineParts[2];

            // 不匹配则保留该行
            if (!(lineTime == time && lineType == type && lineTitle == title))
            {
                keepLines.append(line);
            }
        }
    }
    file.close();

    // 3. 重新写入过滤后的内容
    return rewriteFeedbackFile(keepLines);
}

// 新增：重新写入文件
bool CampusFeedback::rewriteFeedbackFile(const QList<QString> &keepLines)
{
    QFile file("feedback.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return false;

    QTextStream out(&file);
    for (const QString &line : keepLines)
    {
        out << line << "\n";
    }

    file.close();
    return true;
}
