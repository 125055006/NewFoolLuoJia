#ifndef RESETPS_H
#define RESETPS_H

#include <QWidget>
#include<QMessageBox>
#include "userfilemanager.h"

namespace Ui {
class ResetPS;
}

class ResetPS : public QWidget
{
    Q_OBJECT

public:
    explicit ResetPS(QWidget *parent = nullptr);
    ~ResetPS();

private slots:

    void on_Return_clicked();

    void on_Confirm_clicked();

signals:

    void passwordResetSuccess();

private:

    Ui::ResetPS *ui;

};

#endif // RESETPS_H
