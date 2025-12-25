#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QMessageBox>
#include"userfilemanager.h"

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

signals:
    void RegisterSuccess();

private slots:

    void on_ConfirmRegister_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
