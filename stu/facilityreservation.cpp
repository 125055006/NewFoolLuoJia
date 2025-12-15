#include "facilityreservation.h"
#include "ui_facilityreservation.h"
#include <QDateTime>
#include <QSqlError>
facilityreservation::facilityreservation(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::facilityreservation)
{
    ui->setupUi(this);
    // 初始化数据库
    initDatabase();
    // 构建UI
    initUI();
    // 加载历史记录
    loadReservationRecords();
}

facilityreservation::~facilityreservation()
{
    delete ui;
    if (m_db.isOpen()) {
        m_db.close();
    }
}
void facilityreservation::initDatabase()
{
    // 添加SQLite驱动
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    // 数据库文件路径（当前目录）
    m_db.setDatabaseName("./campus_facility.db");

    // 打开数据库
    if (!m_db.open()) {
        QMessageBox::critical(this, "数据库错误",
                              "无法连接数据库：" + m_db.lastError().text());
        return;
    }

    // 创建预约表（不存在则创建）
    QSqlQuery query;
    QString createTableSql = R"(
        CREATE TABLE IF NOT EXISTS reservation (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_name TEXT NOT NULL,
            user_id TEXT NOT NULL,
            facility_type TEXT NOT NULL,
            facility_num TEXT NOT NULL,
            reserve_date TEXT NOT NULL,
            reserve_time TEXT NOT NULL,
            duration INTEGER NOT NULL,
            create_time TEXT NOT NULL,
            status TEXT DEFAULT '待审核'
        )
    )";

    if (!query.exec(createTableSql)) {
        QMessageBox::critical(this, "数据库错误",
                              "创建表失败：" + query.lastError().text());
    }
}

// 纯代码构建UI界面
void facilityreservation::initUI()
{
    // ========== 全局布局 ==========
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    // ========== 标题 ==========
    QLabel *titleLabel = new QLabel("武汉大学场馆预约系统", this);
    QFont titleFont("Microsoft YaHei", 18, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // ========== 预约表单组 ==========
    QGroupBox *formGroup = new QGroupBox("预约信息", this);
    QGridLayout *formLayout = new QGridLayout(formGroup);
    formLayout->setSpacing(15);
    formLayout->setContentsMargins(20, 20, 20, 20);

    // 1. 姓名
    QLabel *nameLabel = new QLabel("姓名：", this);
    m_leUserName = new QLineEdit(this);
    m_leUserName->setPlaceholderText("请输入您的姓名");
    formLayout->addWidget(nameLabel, 0, 0);
    formLayout->addWidget(m_leUserName, 0, 1);

    // 2. 学号/工号
    QLabel *idLabel = new QLabel("学号/工号：", this);
    m_leUserID = new QLineEdit(this);
    m_leUserID->setPlaceholderText("请输入学号或工号");
    formLayout->addWidget(idLabel, 1, 0);
    formLayout->addWidget(m_leUserID, 1, 1);

    // 3. 场馆类型
    QLabel *typeLabel = new QLabel("场馆类型：", this);
    m_cmbFacilityType = new QComboBox(this);
    // 添加支持的场馆类型
    QStringList facilityTypes = {
        "自习室", "讨论室", "实验室",
        "篮球场", "羽毛球场", "会议室", "图书馆座位"
    };
    m_cmbFacilityType->addItems(facilityTypes);
    // 绑定类型切换信号
    connect(m_cmbFacilityType, &QComboBox::currentIndexChanged,
            this, &facilityreservation::onFacilityTypeChanged);
    formLayout->addWidget(typeLabel, 2, 0);
    formLayout->addWidget(m_cmbFacilityType, 2, 1);

    // 4. 场馆编号
    QLabel *numLabel = new QLabel("场馆编号：", this);
    m_leFacilityNum = new QLineEdit(this);
    m_leFacilityNum->setPlaceholderText("请输入场馆编号");
    formLayout->addWidget(numLabel, 3, 0);
    formLayout->addWidget(m_leFacilityNum, 3, 1);

    // 5. 预约日期
    QLabel *dateLabel = new QLabel("预约日期：", this);
    m_dateEdit = new QDateEdit(this);
    m_dateEdit->setDate(QDate::currentDate()); // 默认当前日期
    m_dateEdit->setMinimumDate(QDate::currentDate()); // 禁止选择过去日期
    m_dateEdit->setCalendarPopup(true); // 日历弹窗
    formLayout->addWidget(dateLabel, 4, 0);
    formLayout->addWidget(m_dateEdit, 4, 1);

    // 6. 预约时间
    QLabel *timeLabel = new QLabel("预约时间：", this);
    m_timeEdit = new QTimeEdit(this);
    m_timeEdit->setTime(QTime::currentTime()); // 默认当前时间
    m_timeEdit->setMinimumTime(QTime::currentTime()); // 禁止选择过去时间
    formLayout->addWidget(timeLabel, 5, 0);
    formLayout->addWidget(m_timeEdit, 5, 1);

    // 7. 预约时长
    QLabel *durationLabel = new QLabel("预约时长（小时）：", this);
    m_spinDuration = new QSpinBox(this);
    m_spinDuration->setRange(1, 12); // 1-12小时
    m_spinDuration->setValue(2); // 默认2小时
    formLayout->addWidget(durationLabel, 6, 0);
    formLayout->addWidget(m_spinDuration, 6, 1);

    // 8. 提示标签
    m_labTip = new QLabel("自习室编号示例：XZ-101", this);
    m_labTip->setStyleSheet("color: #666666; font-size: 12px;");
    formLayout->addWidget(m_labTip, 7, 0, 1, 2);

    // ========== 按钮组 ==========
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(20);

    QPushButton *submitBtn = new QPushButton("提交预约", this);
    submitBtn->setStyleSheet("background-color: #409EFF; color: white; border: none; padding: 8px 20px; border-radius: 4px;");
    connect(submitBtn, &QPushButton::clicked, this, &facilityreservation::onSubmitReservation);

    QPushButton *refreshBtn = new QPushButton("刷新记录", this);
    refreshBtn->setStyleSheet("background-color: #67C23A; color: white; border: none; padding: 8px 20px; border-radius: 4px;");
    connect(refreshBtn, &QPushButton::clicked, this, &facilityreservation::onRefreshReservationList);

    btnLayout->addWidget(submitBtn);
    btnLayout->addWidget(refreshBtn);
    btnLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(formGroup);
    mainLayout->addLayout(btnLayout);
    //新增按钮组
    QPushButton *clearBtn = new QPushButton("清空所有记录", this);
    clearBtn->setStyleSheet("background-color: #F56C6C; color: white; border: none; padding: 8px 20px; border-radius: 4px;");
    connect(clearBtn, &QPushButton::clicked, this, &facilityreservation::onClearAllReservations);

    btnLayout->addWidget(submitBtn);
    btnLayout->addWidget(refreshBtn);
    btnLayout->addWidget(clearBtn); // 添加到按钮布局
    btnLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(btnLayout);
//新增
    // ========== 预约记录表格 ==========
    QGroupBox *tableGroup = new QGroupBox("预约记录", this);
    QVBoxLayout *tableLayout = new QVBoxLayout(tableGroup);

    m_tableRecords = new QTableWidget(this);
    // 设置表格列
    QStringList headers = {"ID", "姓名", "场馆类型", "场馆编号", "预约时间", "时长", "状态"};
    m_tableRecords->setColumnCount(headers.size());
    m_tableRecords->setHorizontalHeaderLabels(headers);
    // 表格样式
    m_tableRecords->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止编辑
    m_tableRecords->horizontalHeader()->setStretchLastSection(true); // 最后一列自适应
    m_tableRecords->verticalHeader()->setVisible(false); // 隐藏行号
    m_tableRecords->setSelectionBehavior(QAbstractItemView::SelectRows); // 整行选择

    tableLayout->addWidget(m_tableRecords);
    mainLayout->addWidget(tableGroup);

    // ========== 窗口设置 ==========
    this->setLayout(mainLayout);
    this->setWindowTitle("武汉大学场馆预约系统");
    this->setFixedSize(800, 700); // 固定窗口大小
}

// 验证预约信息
bool facilityreservation::validateReservationInfo()
{
    // 姓名非空
    if (m_leUserName->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入您的姓名！");
        m_leUserName->setFocus();
        return false;
    }

    // 学号/工号非空
    if (m_leUserID->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入学号或工号！");
        m_leUserID->setFocus();
        return false;
    }

    // 场馆编号非空
    if (m_leFacilityNum->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入场馆编号！");
        m_leFacilityNum->setFocus();
        return false;
    }

    return true;
}

// 提交预约
void facilityreservation::onSubmitReservation()
{
    // 验证信息
    if (!validateReservationInfo()) {
        return;
    }

    // 准备插入数据
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO reservation (
            user_name, user_id, facility_type, facility_num,
            reserve_date, reserve_time, duration, create_time
        ) VALUES (?, ?, ?, ?, ?, ?, ?, ?)
    )");

    // 绑定参数
    query.addBindValue(m_leUserName->text().trimmed());
    query.addBindValue(m_leUserID->text().trimmed());
    query.addBindValue(m_cmbFacilityType->currentText());
    query.addBindValue(m_leFacilityNum->text().trimmed());
    query.addBindValue(m_dateEdit->date().toString("yyyy-MM-dd"));
    query.addBindValue(m_timeEdit->time().toString("HH:mm"));
    query.addBindValue(m_spinDuration->value());
    query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

    // 执行插入
    if (query.exec()) {
        QMessageBox::information(this, "预约成功", "预约信息提交成功！等待管理员审核。");
        // 清空表单
        m_leUserName->clear();
        m_leUserID->clear();
        m_leFacilityNum->clear();
        m_spinDuration->setValue(2);
        // 刷新记录
        loadReservationRecords();
    } else {
        QMessageBox::critical(this, "预约失败", "提交失败：" + query.lastError().text());
    }
}

// 切换场馆类型更新提示
void facilityreservation::onFacilityTypeChanged(int index)
{
    QString tipText;
    switch (index) {
    case 0: tipText = "自习室编号示例：XZ-101（如：XZ-101）"; break;
    case 1: tipText = "讨论室编号示例：TL-202（如：TL-202）"; break;
    case 2: tipText = "实验室编号示例：SY-303（如：SY-303）"; break;
    case 3: tipText = "篮球场编号示例：LQ-01（如：LQ-01）"; break;
    case 4: tipText = "羽毛球场编号示例：YM-02（如：YM-02）"; break;
    case 5: tipText = "会议室编号示例：HY-401（如：HY-401）"; break;
    case 6: tipText = "图书馆座位编号示例：TSG-ZW-505（如：TSG-ZW-505）"; break;
    default: tipText = "请输入正确的场馆编号";
    }
    m_labTip->setText(tipText);
}

// 加载预约记录
void facilityreservation::loadReservationRecords()
{
    // 清空表格
    m_tableRecords->setRowCount(0);

    // 查询所有预约记录
    QSqlQuery query("SELECT id, user_name, facility_type, facility_num, "
                    "reserve_date || ' ' || reserve_time, duration, status "
                    "FROM reservation ORDER BY create_time DESC");

    int row = 0;
    while (query.next()) {
        // 添加行
        m_tableRecords->insertRow(row);
        // 填充数据
        m_tableRecords->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        m_tableRecords->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        m_tableRecords->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        m_tableRecords->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        m_tableRecords->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
        m_tableRecords->setItem(row, 5, new QTableWidgetItem(QString("%1小时").arg(query.value(5).toInt())));
        m_tableRecords->setItem(row, 6, new QTableWidgetItem(query.value(6).toString()));

        // 设置状态文字颜色
        QTableWidgetItem *statusItem = m_tableRecords->item(row, 6);
        if (statusItem->text() == "待审核") {
            statusItem->setForeground(Qt::blue);
        } else if (statusItem->text() == "已通过") {
            statusItem->setForeground(Qt::green);
        } else if (statusItem->text() == "已拒绝") {
            statusItem->setForeground(Qt::red);
        }

        row++;
    }

    // 调整列宽
    for (int i = 0; i < m_tableRecords->columnCount() - 1; i++) {
        m_tableRecords->resizeColumnToContents(i);
    }
}

// 刷新预约记录
void facilityreservation::onRefreshReservationList()
{
    loadReservationRecords();
    QMessageBox::information(this, "刷新成功", "预约记录已更新！");
}
void facilityreservation::onClearAllReservations()
{
    // 二次确认，防止误删
    int ret = QMessageBox::warning(this, "警告", "确定要清空所有预约记录吗？此操作不可恢复！",
                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret != QMessageBox::Yes) {
        return; // 用户取消操作
    }

    QSqlQuery query;
    // 执行删除语句，清空reservation表所有数据
    QString deleteSql = "DELETE FROM reservation";
    if (query.exec(deleteSql)) {
        QMessageBox::information(this, "成功", "所有预约记录已清空！");
        loadReservationRecords(); // 刷新表格，让界面同步更新
    } else {
        QMessageBox::critical(this, "错误", "清空失败：" + query.lastError().text());
    }
}
