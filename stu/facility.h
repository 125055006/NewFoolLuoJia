#ifndef FACILITY_H
#define FACILITY_H

#include <QWidget>

// 引入电话黄历逻辑头文件
#include "phonebooklogic.h"
namespace Ui {
class facility;
}

class facility : public QWidget
{
    Q_OBJECT

public:
    explicit facility(QWidget *parent = nullptr);
    ~facility();
private slots:
    void on_btnSearch_clicked();    // 搜索按钮
    void on_btnReset_clicked();     // 重置按钮
    void on_btnAdd_clicked();       // 添加按钮
    void on_btnEdit_clicked();      // 修改按钮
    void on_btnDelete_clicked();    // 删除按钮
private:
    Ui::facility *ui;
    phonebooklogic *m_phoneLogic;   // 电话黄历逻辑实例

    // 加载数据到表格
    void loadPhoneBookData(const QList<PhoneBookInfo> &data);
};

#endif // FACILITY_H
