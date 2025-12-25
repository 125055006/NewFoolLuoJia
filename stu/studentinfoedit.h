#ifndef STUDENTINFOEDIT_H
#define STUDENTINFOEDIT_H

#include <QWidget>
#include <QString>
#include "studentmanager.h"

#include <QWidget>

namespace Ui {
class StudentInfoEdit;
}

class StudentInfoEdit : public QWidget
{
    Q_OBJECT

public:
    explicit StudentInfoEdit(const QString &studentId, QWidget *parent = nullptr);
    ~StudentInfoEdit();


signals:
    // 信号：编辑完成，传递学生ID
    void editCompleted(const QString &studentId);
    // 信号：取消编辑
    void editCancelled();


private slots:
    void on_saveButton_clicked();    // 保存按钮
    void on_cancelButton_clicked();  // 取消按钮
    void on_returnButton_clicked();  // 返回按钮（如果需要）

private:
    Ui::StudentInfoEdit *ui;

    QString currentStudentId;

    // 初始化界面
    void setupUI();
    // 加载学生信息
    void loadStudentInfo();
    // 保存学生信息
    void saveStudentInfo();

};

#endif // STUDENTINFOEDIT_H
