#ifndef CAMPUSINFOWIDGET_H
#define CAMPUSINFOWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMenu>
#include <QContextMenuEvent>
#include <QStandardPaths>

enum InfoType {
    CampusNewsType = 0,    // 校园要闻
    DeptNewsType = 1,      // 院系动态
    NoticeType = 2,        // 通知公告
    LectureType = 3,       // 学术讲座
    EmploymentType = 4     // 就业信息
};

namespace Ui {
class CampusInfoWidget;
}

class CampusInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CampusInfoWidget(QWidget *parent = nullptr);
    ~CampusInfoWidget();

protected:
    // 重写右键菜单事件（实现删除功能）
    void contextMenuEvent(QContextMenuEvent *event) override;

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
     QString m_dataFilePath;         // 数据文件路径

    // 私有方法：数据持久化相关
    void initDataFile();            // 初始化数据文件
    void loadAllData();             // 程序启动时加载所有数据
    void saveInfoToFile(InfoType type, const QString &info); // 保存单条信息到文件
    void deleteInfoFromFile(InfoType type, const QString &info); // 从文件删除信息
    QJsonArray loadInfoFromFile(InfoType type); // 从文件加载指定类型的信息
};

#endif // CAMPUSINFOWIDGET_H
