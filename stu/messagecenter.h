#ifndef MESSAGECENTER_H
#define MESSAGECENTER_H

#include <QWidget>

namespace Ui {
class MessageCenter;
}

class MessageCenter : public QWidget
{
    Q_OBJECT

public:
    explicit MessageCenter(QWidget *parent = nullptr);
    ~MessageCenter();

private:
    Ui::MessageCenter *ui;
};

#endif // MESSAGECENTER_H
