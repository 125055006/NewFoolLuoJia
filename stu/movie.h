#ifndef MOVIE_H
#define MOVIE_H

#include <QWidget>
#include"myclient.h"
namespace Ui {
class movie;
}

class movie : public QWidget
{
    Q_OBJECT

public:
    explicit movie(MyClient *client=nullptr,QWidget *parent = nullptr);
    ~movie();

private slots:
    void on_Return_clicked();
    void ShowMovie(const QString &MovieInfo);

private:
    Ui::movie *ui;
    MyClient *m_client;
};

#endif // MOVIE_H
