#include "SchoolCalendarWidget.h"
#include "ui_SchoolCalendarWidget.h"
#include <QMessageBox>
#include <QDate>
widgetCalendar::widgetCalendar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widgetCalendar)
{
    ui->setupUi(this);
    initTable();       // 初始化表格
    loadCalendarData();// 加载本地数据（首次运行无数据则为空）
    refreshTable();    // 刷新表格展示
}

widgetCalendar::~widgetCalendar()
{
    delete ui;
}
// 初始化表格列（学期、开始日期、结束日期、假期安排）
void widgetCalendar::initTable()
{
    ui->tableCalendar->setColumnCount(4);
    ui->tableCalendar->setHorizontalHeaderLabels({
        tr("学期"), tr("开始日期"), tr("结束日期"), tr("假期安排")
    });
    // 表格属性设置
    ui->tableCalendar->setSelectionBehavior(QAbstractItemView::SelectRows); // 整行选中
    ui->tableCalendar->setEditTriggers(QAbstractItemView::NoEditTriggers);  // 禁止编辑
    ui->tableCalendar->horizontalHeader()->setStretchLastSection(true);     // 最后一列拉伸
}

// 刷新表格：将m_calendarList的数据展示到表格
void widgetCalendar::refreshTable()
{
    ui->tableCalendar->setRowCount(0); // 清空表格
    for (int i = 0; i < m_calendarList.size(); ++i) {
        const CalendarInfo &info = m_calendarList.at(i);
        ui->tableCalendar->insertRow(i); // 插入行
        // 设置单元格数据
        ui->tableCalendar->setItem(i, 0, new QTableWidgetItem(info.semester));
        ui->tableCalendar->setItem(i, 1, new QTableWidgetItem(info.startDate));
        ui->tableCalendar->setItem(i, 2, new QTableWidgetItem(info.endDate));
        ui->tableCalendar->setItem(i, 3, new QTableWidgetItem(info.holiday));
    }
}

// 加载本地校历数据（JSON格式，存储在程序运行目录的calendar.json）
void widgetCalendar::loadCalendarData()
{
    QFile file("calendar.json");
    if (!file.open(QIODevice::ReadOnly)) {
        return; // 无文件则返回，首次运行正常
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (doc.isArray()) {
        QJsonArray arr = doc.array();
        for (const QJsonValue &val : arr) {
            QJsonObject obj = val.toObject();
            CalendarInfo info;
            info.semester = obj["semester"].toString();
            info.startDate = obj["startDate"].toString();
            info.endDate = obj["endDate"].toString();
            info.holiday = obj["holiday"].toString();
            m_calendarList.append(info);
        }
    }
}

// 保存校历数据到本地JSON文件
bool widgetCalendar::saveCalendarData()
{
    QJsonArray arr;
    for (const CalendarInfo &info : m_calendarList) {
        QJsonObject obj;
        obj["semester"] = info.semester;
        obj["startDate"] = info.startDate;
        obj["endDate"] = info.endDate;
        obj["holiday"] = info.holiday;
        arr.append(obj);
    }

    QFile file("calendar.json");
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("错误"), tr("保存文件失败！"));
        return false;
    }
    file.write(QJsonDocument(arr).toJson(QJsonDocument::Indented));
    file.close();
    return true;
}

// ==================== 槽函数（右键转到槽生成）====================
// 新增校历条目
void widgetCalendar::on_btnAdd_clicked()
{
    // 获取输入框数据
    QString semester = ui->editSemester->text().trimmed();
    QString startDate = ui->dateStart->date().toString("yyyy-MM-dd");
    QString endDate = ui->dateEnd->date().toString("yyyy-MM-dd");
    QString holiday = ui->editHoliday->toPlainText().trimmed();

    // 校验必填项
    if (semester.isEmpty()) {
        QMessageBox::warning(this, tr("提示"), tr("请输入学期名称！"));
        return;
    }

    // 检查学期是否重复
    for (const CalendarInfo &info : m_calendarList) {
        if (info.semester == semester) {
            QMessageBox::warning(this, tr("提示"), tr("该学期已存在，请勿重复添加！"));
            return;
        }
    }

    // 添加到数据列表
    CalendarInfo info;
    info.semester = semester;
    info.startDate = startDate;
    info.endDate = endDate;
    info.holiday = holiday;
    m_calendarList.append(info);

    // 刷新表格 + 清空输入框
    refreshTable();
    ui->editSemester->clear();
    ui->editHoliday->clear();
    ui->dateStart->setDate(QDate::currentDate());
    ui->dateEnd->setDate(QDate::currentDate());

    QMessageBox::information(this, tr("提示"), tr("新增校历成功！"));
}

// 修改选中的校历条目
void widgetCalendar::on_btnModify_clicked()
{
    // 获取选中行
    int curRow = ui->tableCalendar->currentRow();
    if (curRow < 0 || curRow >= m_calendarList.size()) {
        QMessageBox::warning(this, tr("提示"), tr("请先选中要修改的校历条目！"));
        return;
    }

    // 获取输入框新数据
    QString semester = ui->editSemester->text().trimmed();
    QString startDate = ui->dateStart->date().toString("yyyy-MM-dd");
    QString endDate = ui->dateEnd->date().toString("yyyy-MM-dd");
    QString holiday = ui->editHoliday->toPlainText().trimmed();

    if (semester.isEmpty()) {
        QMessageBox::warning(this, tr("提示"), tr("请输入学期名称！"));
        return;
    }

    // 检查学期是否重复（排除当前行）
    for (int i = 0; i < m_calendarList.size(); ++i) {
        if (i != curRow && m_calendarList.at(i).semester == semester) {
            QMessageBox::warning(this, tr("提示"), tr("该学期已存在，请勿重复！"));
            return;
        }
    }

    // 更新数据
    CalendarInfo &info = m_calendarList[curRow];
    info.semester = semester;
    info.startDate = startDate;
    info.endDate = endDate;
    info.holiday = holiday;

    // 刷新表格 + 清空输入框
    refreshTable();
    ui->editSemester->clear();
    ui->editHoliday->clear();
    ui->dateStart->setDate(QDate::currentDate());
    ui->dateEnd->setDate(QDate::currentDate());

    QMessageBox::information(this, tr("提示"), tr("修改校历成功！"));
}

// 删除选中的校历条目
void widgetCalendar::on_btnDelete_clicked()
{
    int curRow = ui->tableCalendar->currentRow();
    if (curRow < 0 || curRow >= m_calendarList.size()) {
        QMessageBox::warning(this, tr("提示"), tr("请先选中要删除的校历条目！"));
        return;
    }

    // 确认删除
    if (QMessageBox::question(this, tr("确认"), tr("是否删除选中的校历条目？"),
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    // 移除数据并刷新
    m_calendarList.removeAt(curRow);
    refreshTable();
    QMessageBox::information(this, tr("提示"), tr("删除校历成功！"));
}

// 保存校历数据到本地文件
void widgetCalendar::on_btnSave_clicked()
{
    if (m_calendarList.isEmpty()) {
        QMessageBox::warning(this, tr("提示"), tr("暂无校历数据可保存！"));
        return;
    }

    if (saveCalendarData()) {
        QMessageBox::information(this, tr("提示"), tr("校历数据保存成功！"));
    } else {
        QMessageBox::critical(this, tr("错误"), tr("校历数据保存失败！"));
    }
}
