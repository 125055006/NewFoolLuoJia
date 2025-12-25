#include "studentmanager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QStandardPaths>

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
    // 获取应用程序的绝对路径
    QString appPath = QCoreApplication::applicationFilePath();
    qDebug() << "应用程序路径：" << appPath;

    // 分析路径，找到项目根目录
    QFileInfo appInfo(appPath);
    QDir currentDir = appInfo.dir();  // 当前执行目录

    // 向上查找，直到找到 NewFoolLuoJia 目录
    QString projectRoot;
    while (!currentDir.isRoot()) {
        QString dirName = currentDir.dirName();

        if (dirName == "NewFoolLuoJia") {
            projectRoot = currentDir.path();
            break;
        }

        if (!currentDir.cdUp()) {
            break;
        }
    }

    if (projectRoot.isEmpty()) {
        // 没找到，使用备用方案
        projectRoot = QCoreApplication::applicationDirPath();
        qDebug() << "警告：未找到项目根目录，使用应用程序目录";
    }

    // 创建 config 目录
    QString configDir = QDir(projectRoot).filePath("config");
    QDir configDirObj(configDir);
    if (!configDirObj.exists()) {
        configDirObj.mkpath(".");
        qDebug() << "创建配置目录：" << configDir;
    }

    dataFile = configDirObj.filePath("students.dat");
    qDebug() << "数据文件路径：" << dataFile;

    loadFromFile(dataFile);
}

StudentManager& StudentManager::instance()
{
    static StudentManager instance;
    return instance;
}

bool StudentManager::addOrUpdateStudent(const StudentInfo &info)
{
    if(info.id.isEmpty() || info.name.isEmpty()) {
        qDebug() << "学生信息不完整，无法保存";
        return false;
    }

    qDebug() << "保存学生信息：" << info.id << info.name;
    students[info.id] = info;
    bool success = saveToFile(dataFile);

    if(success) {
        qDebug() << "学生信息已保存到：" << dataFile;
    } else {
        qDebug() << "保存学生信息失败";
    }

    return success;
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
