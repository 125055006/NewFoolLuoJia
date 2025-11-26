#ifndef STUMENU_H
#define STUMENU_H

#include <QWidget>
#include"student.h"
namespace Ui {
class StuMenu;
}

class StuMenu : public QWidget
{
    Q_OBJECT

public:
    explicit StuMenu(QWidget *parent = nullptr);
    ~StuMenu();

private slots:
    void on_PersonCenter_clicked();

private:
    Ui::StuMenu *ui;
    Student *stu;
};

#endif // STUMENU_H
