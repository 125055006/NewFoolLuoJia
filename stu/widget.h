#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"myclient.h"
#include"stumenu.h"
#include"student.h"
#include"resetps.h"
#include"choosecourse.h"
#include"consultscore.h"
#include"stu_comment.h"
#include<QMessageBox>
#include<service.h>
#include<facilityreservation.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_login_clicked();

    void on_ResetPS_clicked();

    void NewIdAndPs(const QString &new_id,const QString &new_ps);
private:
    QString Cur_id;
    QString Cur_Ps;
    Ui::Widget *ui;
    MyClient *client;
    StuMenu *stu_menu;
    Student *stu_ui;
    ResetPS *set_ps;
    ChooseCourse *cos_client;
    ConsultScore *con_sco;
    stu_comment *stu_com;
};
#endif // WIDGET_H
