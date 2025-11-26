#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"myserver.h"
#include"record.h"
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

private:
    Ui::Widget *ui;
    MyServer *server;
    Record *re_cord;
};
#endif // WIDGET_H
