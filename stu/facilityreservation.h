#ifndef FACILITYRESERVATION_H
#define FACILITYRESERVATION_H
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QGroupBox>

namespace Ui {
class facilityreservation;
}

class facilityreservation : public QWidget
{
    Q_OBJECT

public:
    explicit facilityreservation(QWidget *parent = nullptr);
    ~facilityreservation();
private slots:
    // 提交预约
    void onSubmitReservation();
    // 刷新预约列表
    void onRefreshReservationList();
    // 切换场馆类型更新提示
    void onFacilityTypeChanged(int index);
    // 新增清空记录的槽函数
    void onClearAllReservations();
private:
    Ui::facilityreservation *ui;
    // 初始化数据库（SQLite）
    void initDatabase();
    // 构建UI界面
    void initUI();
    // 验证预约信息
    bool validateReservationInfo();
    // 加载历史预约记录
    void loadReservationRecords();

    // 数据库对象
    QSqlDatabase m_db;

    // UI控件
    QLineEdit *m_leUserName;    // 姓名输入框
    QLineEdit *m_leUserID;      // 学号/工号输入框
    QComboBox *m_cmbFacilityType; // 场馆类型下拉框
    QLineEdit *m_leFacilityNum; // 场馆编号输入框
    QDateEdit *m_dateEdit;      // 预约日期选择
    QTimeEdit *m_timeEdit;      // 预约时间选择
    QSpinBox *m_spinDuration;   // 预约时长（小时）
    QLabel *m_labTip;           // 提示标签
    QTableWidget *m_tableRecords; // 预约记录表格
};

#endif // FACILITYRESERVATION_H
