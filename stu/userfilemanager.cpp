#include "userfilemanager.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>

UserFileManager::UserFileManager()
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

    m_filename = configDirObj.filePath("users.txt");
    qDebug() << "数据文件路径：" << m_filename;

    loadAllUsers();
}

UserFileManager::~UserFileManager()
{
    // 自动保存用户数据
    saveAllUsers();
}

UserFileManager& UserFileManager::instance()
{
    static UserFileManager instance;
    return instance;
}

bool UserFileManager::loadAllUsers()
{
    QFile file(m_filename);//读取

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // 文件不存在，创建默认用户
        qDebug() << "用户文件不存在，创建默认用户";
        m_users.clear();  // 清空现有数据
        m_users["20250001"] = "123456";   // 原始用户
        m_users["20251001"] = "123456";   // 测试用户1
        m_users["20251002"] = "123456";   // 测试用户2
        return saveAllUsers();         // 保存默认用户
    }

    QTextStream in(&file);//文本读取流

    m_users.clear();//清空旧数据

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();//行读取，去空格。

        if (line.isEmpty() || line.startsWith("#")) {
            continue;  // 跳过
        }

        QStringList parts = line.split(":");
        //各式为“用户：密码”，用来解析。

        if (parts.size() >= 2) {
            QString id = parts[0].trimmed();
            QString password = parts[1].trimmed();
            if (!id.isEmpty() && !password.isEmpty()) {
                m_users[id] = password;
            }
        }
    }

    file.close();

    // 如果文件是空的，添加默认用户
    if (m_users.isEmpty()) {

        m_users["20250000"] = "123456";

        saveAllUsers();
    }

    return true;
}

bool UserFileManager::saveAllUsers()
{
    QFile file(m_filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        qDebug() << "无法打开用户文件进行写入:" << file.errorString();

        return false;
    }

    QTextStream out(&file);

    out << "# 用户数据文件格式：用户名:密码\n";

    out << "# 每行一个用户，格式：用户名:密码\n\n";
    //写入注解

    QMapIterator<QString, QString> it(m_users);

    while (it.hasNext()) {

        it.next();

        out << it.key() << ":" << it.value() << "\n";//写入文件
    }

    file.close();

    return true;
}

bool UserFileManager::addUser(const QString &id, const QString &password)
{
    if (id.isEmpty() || password.isEmpty()) {
        qDebug() << "添加用户失败：用户名或密码为空";
        return false;
    }

    // 检查用户是否已存在
    if (m_users.contains(id)) {
        qDebug() << "添加用户失败：用户" << id << "已存在";
        return false;
    }

    m_users[id] = password;

    bool success = saveAllUsers();

    if (success) {
        qDebug() << "添加用户成功：" << id;
    } else {
        qDebug() << "添加用户失败：保存文件出错";
    }
    return success;
}

bool UserFileManager::validateUser(const QString &id, const QString &password) const
{
    if (!m_users.contains(id)) {
        qDebug() << "用户验证失败：用户" << id << "不存在";
        return false;
    }

    bool valid = (m_users[id] == password);
    if (valid) {
        qDebug() << "用户验证成功：" << id;
    } else {
        qDebug() << "用户验证失败：密码错误";
    }
    return valid;
}

bool UserFileManager::userExists(const QString &id) const
{
    return m_users.contains(id);
}

bool UserFileManager::resetPassword(const QString &id, const QString &newPassword)
{
    if (!userExists(id)) {
        qDebug() << "重置密码失败：用户" << id << "不存在";
        return false;
    }

    if (newPassword.isEmpty()) {
        qDebug() << "重置密码失败：新密码为空";
        return false;
    }

    m_users[id] = newPassword;
    bool success = saveAllUsers();

    if (success) {
        qDebug() << "重置密码成功：" << id;
    } else {
        qDebug() << "重置密码失败：保存文件出错";
    }

    return success;
}
