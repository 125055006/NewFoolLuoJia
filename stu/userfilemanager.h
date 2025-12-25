#ifndef USERFILEMANAGER_H
#define USERFILEMANAGER_H

#include <QString>
#include <QMap>

class UserFileManager
{
public:
    static UserFileManager& instance();

    bool loadAllUsers();

    bool saveAllUsers();

    bool addUser(const QString &id, const QString &password);

    bool validateUser(const QString &id, const QString &password) const;

    bool resetPassword(const QString &id, const QString &newPassword);

    QMap<QString, QString> getAllUsers() const { return m_users; }

    bool userExists(const QString &id) const;

private:
    UserFileManager();

    ~UserFileManager();

    UserFileManager(const UserFileManager&) = delete;

    UserFileManager& operator=(const UserFileManager&) = delete;

    QMap<QString, QString> m_users;

    QString m_filename;
};

#endif // USERFILEMANAGER_H
