#ifndef CAMPUSINFOWIDGET_H
#define CAMPUSINFOWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QMessageBox>
namespace Ui {
class CampusInfoWidget;
}

class CampusInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CampusInfoWidget(QWidget *parent = nullptr);
    ~CampusInfoWidget();
private slots:
    // 校园要闻相关槽函数
    void on_btnAddCampusNews_clicked();

    // 院系动态相关槽函数
    void on_btnAddDeptNews_clicked();

    // 通知公告相关槽函数
    void on_btnAddNotice_clicked();

    // 学术讲座相关槽函数
    void on_btnAddLecture_clicked();
    void on_btnSignUpLecture_clicked();

    // 就业信息相关槽函数
    void on_btnAddEmployment_clicked();

private:
    Ui::CampusInfoWidget *ui;
    bool m_lectureSignedUp = false; // 标记讲座报名状态
};

#endif // CAMPUSINFOWIDGET_H
