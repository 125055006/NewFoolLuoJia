#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H
#include <QString>
#include <QList>
#include <QMap>

class StudentInfo
{
public:
    QString id;         // 学号
    QString name;       // 姓名
    QString gender;     // 性别
    QString age;        // 年龄
    QString major;      // 专业
    QString className;  // 班级
    QString phone;      // 电话号码
    QString address;    // 家庭住址

    // 转换为字符串格式（用于保存到文件）
    QString toString() const;

    // 从字符串解析
    static StudentInfo fromString(const QString &str);
};

class StudentManager
{
public:
    static StudentManager& instance();

    // 添加/更新学生信息
    bool addOrUpdateStudent(const StudentInfo &info);

    // 根据学号获取学生信息
    StudentInfo getStudentById(const QString &id) const;

    // 删除学生信息
    void removeStudent(const QString &id);

    // 获取所有学生信息
    QList<StudentInfo> getAllStudents() const;

    // 从文件加载
    bool loadFromFile(const QString &filename = "students.dat");

    // 保存到文件
    bool saveToFile(const QString &filename = "students.dat") const;

    // 检查学号是否存在
    bool exists(const QString &id) const;

private:
    StudentManager();

    StudentManager(const StudentManager&) = delete;

    StudentManager& operator=(const StudentManager&) = delete;

    QMap<QString, StudentInfo> students;  // 用学号作为键存储学生信息

    QString dataFile;
};

#endif // STUDENTMANAGER_H
