#ifndef STUDENT_H
#define STUDENT_H

#include <QWidget>
#include"myclient.h"
#include<QMessageBox>
#include <QContextMenuEvent>  // 添加：用于右键菜单

namespace Ui {
class Student;
}

class Student : public QWidget
{
    Q_OBJECT

public:
    explicit Student(MyClient *client=nullptr,QWidget *parent = nullptr);

    ~Student();

    void setStudentId(const QString &id);

    void loadStudentInfoFromLocal();

    void refreshStudentInfo();


protected:
    // 新增：右键菜单事件
    void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
    void on_Return_clicked();

    void onReceiveStuInfo(const QString &info);

    void on_EditStudent_clicked();

    void on_RefreshBtn_clicked();

    void onRefreshAction();

private:
    Ui::Student *ui;

    MyClient *m_client;

    QString currentStudentId;

    QAction *refreshAction;

    void createContextMenu();  // 创建右键菜单

};

#endif // STUDENT_H
