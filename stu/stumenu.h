#ifndef STUMENU_H
#define STUMENU_H

#include <QWidget>
#include"student.h"
#include"myclient.h"
#include"choosecourse.h"
#include"consultscore.h"
#include"borrowbook.h"
#include"stu_comment.h"
#include"stuacti.h"
#include"campuslife.h"
namespace Ui {
class StuMenu;
}

class StuMenu : public QWidget
{
    Q_OBJECT

public:
    explicit StuMenu(MyClient *client=nullptr,Student *student=nullptr,QWidget *parent = nullptr);
    ~StuMenu();

private slots:
    void on_PersonCenter_clicked();

    void on_choose_course_clicked();

    void on_Con_Sco_clicked();

    void on_stu_com_clicked();

    void on_bor_book_clicked();



    void on_stu_actiButton_clicked();

    void on_campusButton_clicked();

private:
    Ui::StuMenu *ui;
    Student *stu;
    ChooseCourse *cos_cos;
    ConsultScore *con_sco;
    stu_comment *stu_com;
    BorrowBook *bor_book;
    MyClient *m_client;
    StuActi *s_acti;
    CampusLife *campus;
};

#endif // STUMENU_H
