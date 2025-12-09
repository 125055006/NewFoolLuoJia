#ifndef GETCOMMENT_H
#define GETCOMMENT_H

#include <QWidget>
#include"myserver.h"
namespace Ui {
class GetComment;
}

class GetComment : public QWidget
{
    Q_OBJECT

public:
    explicit GetComment(MyServer *server,QWidget *parent = nullptr);
    ~GetComment();

private slots:
    void on_pushButton_clicked();
    void GetCom(const QString &com_Info);

    void on_confirm_clicked();

private:
    Ui::GetComment *ui;
    MyServer *m_server;
};

#endif // GETCOMMENT_H
