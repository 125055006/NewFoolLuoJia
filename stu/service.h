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

private slots:
    void on_facilityreservation_clicked();

    void on_telephone_clicked();

    void on_pushButton_clicked();

private:
    Ui::service *ui;
};

#endif // SERVICE_H
