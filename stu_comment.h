#ifndef STU_COMMENT_H
#define STU_COMMENT_H

#include <QWidget>
#include<QMessageBox>
#include"myclient.h"
namespace Ui {
class stu_comment;
}

class stu_comment : public QWidget
{
    Q_OBJECT

public:
    explicit stu_comment(MyClient *client,QWidget *parent = nullptr);
    ~stu_comment();

private slots:
    void on_Return_clicked();

    void on_confirm_clicked();

    void Resepon();
private:
    Ui::stu_comment *ui;
    QString com_Info;
    MyClient *m_client;
};

#endif // STU_COMMENT_H
