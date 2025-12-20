#ifndef PUBLISHMOVIE_H
#define PUBLISHMOVIE_H

#include <QWidget>
#include"myserver.h"
#include<QDebug>
#include<QMessageBox>
namespace Ui {
class PublishMovie;
}

class PublishMovie : public QWidget
{
    Q_OBJECT

public:
    explicit PublishMovie(MyServer *server=nullptr,QWidget *parent = nullptr);
    ~PublishMovie();

private slots:
    void on_Return_clicked();

    void on_Publish_clicked();

private:
    Ui::PublishMovie *ui;
    MyServer *m_server;
};

#endif // PUBLISHMOVIE_H
