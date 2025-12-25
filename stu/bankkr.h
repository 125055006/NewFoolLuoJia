#ifndef BANKKR_H
#define BANKKR_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class BankKr;
}

class BankKr : public QWidget
{
    Q_OBJECT

public:
    explicit BankKr(QWidget *parent = nullptr);
    ~BankKr();

private slots:
    void on_exitButton_clicked();
    void krComboBoxChanged();

    void on_commitButton_clicked();

signals:
    void krHadExit();
    void sendMoney(const QString &mon);

private:
    Ui::BankKr *ui;
};

#endif // BANKKR_H
