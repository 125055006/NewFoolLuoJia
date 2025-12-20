#ifndef SCHOOLCALENDARWIDGET_H
#define SCHOOLCALENDARWIDGET_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
// 校历数据结构体
struct CalendarInfo {
    QString semester;    // 学期名称
    QString startDate;   // 学期开始日期（字符串格式：yyyy-MM-dd）
    QString endDate;     // 学期结束日期
    QString holiday;     // 假期安排
};
namespace Ui {
class widgetCalendar;
}

class widgetCalendar : public QWidget
{
    Q_OBJECT

public:
    explicit widgetCalendar(QWidget *parent = nullptr);
    ~widgetCalendar();
private slots:
    // 右键转到槽生成的槽函数（命名规则不变，仅归属类变化）
    void on_btnAdd_clicked();       // 新增校历
    void on_btnModify_clicked();  // 修改校历
    void on_btnDelete_clicked();   // 删除校历
    void on_btnSave_clicked();     // 保存校历

private:
    Ui::widgetCalendar *ui;
    QList<CalendarInfo> m_calendarList; // 存储所有校历数据

    // 辅助函数
    void initTable();               // 初始化表格列
    void refreshTable();            // 刷新表格展示
    void loadCalendarData();        // 加载本地校历数据（可选）
    bool saveCalendarData();        // 保存校历数据到本地文件
};

#endif // SCHOOLCALENDARWIDGET_H
