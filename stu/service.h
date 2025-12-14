#ifndef SERVICE_H
#define SERVICE_H

#include <QWidget>

namespace Ui {
class service;
}

class service : public QWidget
{
    Q_OBJECT

public:
    explicit service(QWidget *parent = nullptr);
    ~service();

private:
    Ui::service *ui;
};

#endif // SERVICE_H
