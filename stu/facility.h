#ifndef FACILITY_H
#define FACILITY_H

#include <QWidget>

namespace Ui {
class facility;
}

class facility : public QWidget
{
    Q_OBJECT

public:
    explicit facility(QWidget *parent = nullptr);
    ~facility();

private:
    Ui::facility *ui;
};

#endif // FACILITY_H
