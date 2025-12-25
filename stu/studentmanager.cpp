#include "studentmanager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
QString StudentInfo::toString() const
{
    return QString("%1/%2/%3/%4/%5/%6/%7/%8")
    .arg(id)
        .arg(name)
        .arg(gender)
        .arg(age)
        .arg(major)
        .arg(className)
        .arg(phone)
        .arg(address);
}

StudentInfo StudentInfo::fromString(const QString &str)
{
    StudentInfo info;
    QStringList parts = str.split('/');

    if (parts.size() >= 8) {
        info.id = parts[0];
        info.name = parts[1];
        info.gender = parts[2];
        info.age = parts[3];
        info.major = parts[4];
        info.className = parts[5];
        info.phone = parts[6];
        info.address = parts[7];
    }

    return info;
}

StudentManager::StudentManager()
{
    // 获取应用程序目录
    QString appDir = QCoreApplication::applicationDirPath();

    // 确保 data 目录存在
    QDir dir(appDir);
    if (!dir.exists("data")) {
        dir.mkdir("data");
    }

    dataFile = appDir + "/data/students.dat";

    qDebug() << "学生数据文件路径：" << dataFile;

    loadFromFile(dataFile);
}

StudentManager& StudentManager::instance()
{
    static StudentManager instance;
    return instance;
}

void StudentManager::addOrUpdateStudent(const StudentInfo &info)
{
    students[info.id] = info;
    saveToFile(dataFile);
}

StudentInfo StudentManager::getStudentById(const QString &id) const
{
    if (students.contains(id)) {
        return students[id];
    }
    return StudentInfo();  // 返回空对象
}

void StudentManager::removeStudent(const QString &id)
{
    if (students.contains(id)) {
        students.remove(id);
        saveToFile(dataFile);
    }
}

QList<StudentInfo> StudentManager::getAllStudents() const
{
    return students.values();
}

bool StudentManager::loadFromFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件:" << filename;
        return false;
    }

    students.clear();
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            StudentInfo info = StudentInfo::fromString(line);
            if (!info.id.isEmpty()) {
                students[info.id] = info;
            }
        }
    }

    file.close();
    qDebug() << "已加载" << students.size() << "个学生信息";
    return true;
}

bool StudentManager::saveToFile(const QString &filename) const
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法保存文件:" << filename;
        return false;
    }

    QTextStream out(&file);

    foreach (const StudentInfo &info, students.values()) {
        out << info.toString() << "\n";
    }

    file.close();
    qDebug() << "已保存" << students.size() << "个学生信息";
    return true;
}

bool StudentManager::exists(const QString &id) const
{
    return students.contains(id);
}
