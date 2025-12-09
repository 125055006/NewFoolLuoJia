#ifndef RESETPS_H
#define RESETPS_H

#include <QWidget>
#include<QMessageBox>
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
    void SendNewIdAndPs(const QString &new_id,const QString &new_Ps);
private:
    Ui::ResetPS *ui;
};

#endif // RESETPS_H
