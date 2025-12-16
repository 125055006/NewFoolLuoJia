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

private:
    Ui::CampusFeedback *ui;

    // 私有函数：加载本地反馈数据到列表
    void loadFeedbackData();

    // 私有函数：保存新反馈到本地文件
    bool saveFeedback(const QString &type, const QString &title, const QString &content);

};

#endif // CAMPUSFEEDBACK_H
