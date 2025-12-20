#ifndef MESSAGECENTER_H
#define MESSAGECENTER_H

#include <QWidget>

class QListWidgetItem;

namespace Ui {
class MessageCenter;
}

class MessageCenter : public QWidget
{
    Q_OBJECT

public:
    explicit MessageCenter(QWidget *parent = nullptr);
    ~MessageCenter();

private slots:
    void on_AllNotification_clicked();

    void on_Notification_clicked();

    void on_Todo_clicked();

    void on_Content_itemDoubleClicked(QListWidgetItem *item);

    void on_Content_itemClicked(QListWidgetItem *item);

private:
    Ui::MessageCenter *ui;
    QString defaultStyle;
    QString selectedStyle;
};

#endif // MESSAGECENTER_H
