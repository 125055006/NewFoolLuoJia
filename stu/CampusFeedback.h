#ifndef CAMPUSFEEDBACK_H
#define CAMPUSFEEDBACK_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>

namespace Ui {
class CampusFeedback;
}

class CampusFeedback : public QWidget
{
    Q_OBJECT

public:
    explicit CampusFeedback(QWidget *parent = nullptr);
    ~CampusFeedback();

private slots:
    // 提交反馈按钮槽函数
    void on_btnAdd_clicked();

    // 清空输入按钮槽函数
    void on_btnClear_clicked();

    // 新增删除按钮槽函数
    void on_btnDelete_clicked();

private:
    Ui::CampusFeedback *ui;

    // 私有函数：加载本地反馈数据到列表
    void loadFeedbackData();

    // 私有函数：保存新反馈到本地文件
    bool saveFeedback(const QString &type, const QString &title, const QString &content);
    // 新增私有函数：删除指定反馈记录
    bool deleteFeedback(const QString &itemText);
    // 辅助函数：重新写入文件（删除后刷新）
    bool rewriteFeedbackFile(const QList<QString> &keepLines);
};

#endif // CAMPUSFEEDBACK_H
