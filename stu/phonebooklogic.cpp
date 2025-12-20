#include "phonebooklogic.h"
#include "ui_phonebooklogic.h"

phonebooklogic::phonebooklogic(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::phonebooklogic)
{
    ui->setupUi(this);
}

phonebooklogic::~phonebooklogic()
{
    delete ui;
    if (m_db.isOpen()) {
        m_db.close();
    }
}
// 初始化数据库
bool phonebooklogic::initDatabase(const QString &dbPath)
{
    // 避免重复连接
    if (QSqlDatabase::contains("phonebook_conn")) {
        m_db = QSqlDatabase::database("phonebook_conn");
    } else {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "phonebook_conn");
    }

    m_db.setDatabaseName(dbPath);
    if (!m_db.open()) {
        qWarning() << "数据库打开失败：" << m_db.lastError().text();
        return false;
    }

    // 创建表
    QSqlQuery query(m_db);
    QString createSql = R"(
        CREATE TABLE IF NOT EXISTS phone_book (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            dept_name TEXT NOT NULL,
            contact_person TEXT,
            phone_num TEXT NOT NULL,
            office_addr TEXT,
            remark TEXT
        )
    )";

    if (!query.exec(createSql)) {
        qWarning() << "创建表失败：" << query.lastError().text();
        return false;
    }

    // 初始化默认数据
    initDefaultData();
    return true;
}

// 填充默认常用部门数据
void phonebooklogic::initDefaultData()
{
    QSqlQuery query(m_db);
    query.exec("SELECT COUNT(*) FROM phone_book");
    if (query.next() && query.value(0).toInt() == 0) {
        // 批量插入默认数据
        QList<PhoneBookInfo> defaultData = {
            {1, "教务处", "张老师", "027-68752345", "行政楼101室", "工作时间：8:30-17:30（周末休息）"},
            {2, "图书馆", "李老师", "027-68756789", "图书馆1楼服务台", "工作时间：8:00-22:00"},
            {3, "学生事务中心", "王老师", "027-68751111", "学生活动中心205室", "工作时间：9:00-18:00"},
            {4, "保卫处", "赵警官", "027-68759999", "保卫处办公楼", "24小时值班"},
            {5, "校医院", "陈医生", "027-68758888", "校医院1楼急诊室", "24小时接诊"},
            {6, "后勤保障部", "刘师傅", "027-68757777", "后勤楼302室", "工作时间：8:00-17:00"},
            {7, "财务处", "孙老师", "027-68755555", "行政楼208室", "工作时间：8:30-12:00 14:00-17:30"}
        };

        m_db.transaction();
        query.prepare(R"(
            INSERT INTO phone_book (dept_name, contact_person, phone_num, office_addr, remark)
            VALUES (?, ?, ?, ?, ?)
        )");

        for (const auto &info : defaultData) {
            query.addBindValue(info.deptName);
            query.addBindValue(info.contactPerson);
            query.addBindValue(info.phoneNum);
            query.addBindValue(info.officeAddr);
            query.addBindValue(info.remark);
            query.exec();
        }
        m_db.commit();
    }
}

// 模糊搜索
QList<PhoneBookInfo> phonebooklogic::searchPhoneBook(const QString &keyword)
{
    QList<PhoneBookInfo> result;
    if (!m_db.isOpen()) return result;

    QSqlQuery query(m_db);
    query.prepare(R"(
        SELECT id, dept_name, contact_person, phone_num, office_addr, remark
        FROM phone_book
        WHERE dept_name LIKE ?
        OR contact_person LIKE ?
        OR phone_num LIKE ?
        OR office_addr LIKE ?
        ORDER BY dept_name ASC
    )");

    QString searchKey = "%" + keyword.trimmed() + "%";
    query.addBindValue(searchKey);
    query.addBindValue(searchKey);
    query.addBindValue(searchKey);
    query.addBindValue(searchKey);

    if (query.exec()) {
        while (query.next()) {
            PhoneBookInfo info;
            info.id = query.value(0).toInt();
            info.deptName = query.value(1).toString();
            info.contactPerson = query.value(2).toString();
            info.phoneNum = query.value(3).toString();
            info.officeAddr = query.value(4).toString();
            info.remark = query.value(5).toString();
            result.append(info);
        }
    }

    return result;
}

// 获取所有记录
QList<PhoneBookInfo> phonebooklogic::getAllPhoneBook()
{
    QList<PhoneBookInfo> result;
    if (!m_db.isOpen()) return result;

    QSqlQuery query(m_db);
    query.exec(R"(
        SELECT id, dept_name, contact_person, phone_num, office_addr, remark
        FROM phone_book
        ORDER BY dept_name ASC
    )");

    while (query.next()) {
        PhoneBookInfo info;
        info.id = query.value(0).toInt();
        info.deptName = query.value(1).toString();
        info.contactPerson = query.value(2).toString();
        info.phoneNum = query.value(3).toString();
        info.officeAddr = query.value(4).toString();
        info.remark = query.value(5).toString();
        result.append(info);
    }

    return result;
}

// 添加记录
bool phonebooklogic::addPhoneBook(const PhoneBookInfo &info, QString &outMsg)
{
    if (!m_db.isOpen()) {
        outMsg = "数据库未连接！";
        return false;
    }

    if (info.deptName.isEmpty() || info.phoneNum.isEmpty()) {
        outMsg = "部门名称和联系电话不能为空！";
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare(R"(
        INSERT INTO phone_book (dept_name, contact_person, phone_num, office_addr, remark)
        VALUES (?, ?, ?, ?, ?)
    )");

    query.addBindValue(info.deptName.trimmed());
    query.addBindValue(info.contactPerson.trimmed());
    query.addBindValue(info.phoneNum.trimmed());
    query.addBindValue(info.officeAddr.trimmed());
    query.addBindValue(info.remark.trimmed());

    if (query.exec()) {
        outMsg = "添加成功！";
        return true;
    } else {
        outMsg = "添加失败：" + query.lastError().text();
        return false;
    }
}

// 修改记录
bool phonebooklogic::editPhoneBook(const PhoneBookInfo &info, QString &outMsg)
{
    if (!m_db.isOpen() || info.id == -1) {
        outMsg = "无效的记录！";
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare(R"(
        UPDATE phone_book
        SET dept_name = ?, contact_person = ?, phone_num = ?, office_addr = ?, remark = ?
        WHERE id = ?
    )");

    query.addBindValue(info.deptName.trimmed());
    query.addBindValue(info.contactPerson.trimmed());
    query.addBindValue(info.phoneNum.trimmed());
    query.addBindValue(info.officeAddr.trimmed());
    query.addBindValue(info.remark.trimmed());
    query.addBindValue(info.id);

    if (query.exec() && query.numRowsAffected() > 0) {
        outMsg = "修改成功！";
        return true;
    } else {
        outMsg = "修改失败：" + query.lastError().text();
        return false;
    }
}

// 删除记录
bool phonebooklogic::deletePhoneBook(int id, QString &outMsg)
{
    if (!m_db.isOpen()) {
        outMsg = "数据库未连接！";
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare("DELETE FROM phone_book WHERE id = ?");
    query.addBindValue(id);

    if (query.exec() && query.numRowsAffected() > 0) {
        outMsg = "删除成功！";
        return true;
    } else {
        outMsg = "删除失败：" + query.lastError().text();
        return false;
    }
}

// 查询结果转结构体
PhoneBookInfo phonebooklogic::queryToPhoneBook(const QSqlQuery &query)
{
    PhoneBookInfo info;
    info.id = query.value("id").toInt();
    info.deptName = query.value("dept_name").toString();
    info.contactPerson = query.value("contact_person").toString();
    info.phoneNum = query.value("phone_num").toString();
    info.officeAddr = query.value("office_addr").toString();
    info.remark = query.value("remark").toString();
    return info;
}

