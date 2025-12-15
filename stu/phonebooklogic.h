#ifndef PHONEBOOKLOGIC_H
#define PHONEBOOKLOGIC_H

#include <QWidget>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QList>
// 电话黄历数据结构体
struct PhoneBookInfo {
    int id = -1;                  // 主键ID
    QString deptName;             // 部门名称
    QString contactPerson;        // 联系人
    QString phoneNum;             // 联系电话
    QString officeAddr;           // 办公地址
    QString remark;               // 备注（工作时间等）
};
namespace Ui {
class phonebooklogic;
}

class phonebooklogic : public QWidget
{
    Q_OBJECT

public:
    explicit phonebooklogic(QWidget *parent = nullptr);
    ~phonebooklogic();
    // 初始化数据库（创建表+默认数据）
    bool initDatabase(const QString &dbPath = "./campus_phonebook.db");

    // 模糊搜索（部门/电话/地址/联系人）
    QList<PhoneBookInfo> searchPhoneBook(const QString &keyword);

    // 获取所有记录
    QList<PhoneBookInfo> getAllPhoneBook();

    // 添加新记录
    bool addPhoneBook(const PhoneBookInfo &info, QString &outMsg);

    // 修改记录
    bool editPhoneBook(const PhoneBookInfo &info, QString &outMsg);

    // 删除记录
    bool deletePhoneBook(int id, QString &outMsg);
private:
    Ui::phonebooklogic *ui;
    QSqlDatabase m_db; // 数据库对象

    // 初始化默认数据（首次运行填充）
    void initDefaultData();

    // 查询结果转结构体
    PhoneBookInfo queryToPhoneBook(const QSqlQuery &query);
};

#endif // PHONEBOOKLOGIC_H
