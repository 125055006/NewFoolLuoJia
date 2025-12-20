#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"myserver.h"
#include"record.h"
#include"stucheck.h"
#include"addscore.h"
#include"getcomment.h"
#include"onlinelib.h"
#include"teaclub.h"
#include"campuslife.h"
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
    void on_Record_clicked();

    void on_StuCheck_clicked();

    void on_AddScore_clicked();

    void on_Look_com_clicked();

    void on_book_mng_clicked();

    void on_clubButton_clicked();

    void on_campusButton_clicked();

private:
    Ui::Widget *ui;
    MyServer *server;
    Record *re_cord;
    StuCheck *stu_check;
    AddScore *add_score;
    GetComment *get_com;
    OnlineLib *online_lib;
    TeaClub *tea_club;
    CampusLife *campus;

};
#endif // WIDGET_H
