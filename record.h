#ifndef RECORD_H
#define RECORD_H

#include <QWidget>

namespace Ui {
class Record;
}

class Record : public QWidget
{
    Q_OBJECT

public:
    explicit Record(QWidget *parent = nullptr);
    ~Record();

private slots:
    void on_Save_clicked();

signals:
    void GetStuInfo(const QString &info);
private:
    Ui::Record *ui;

};

#endif // RECORD_H
