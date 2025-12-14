#include "service.h"
#include "ui_service.h"
#include"facilityreservation.h"
service::service(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::service)
{
    ui->setupUi(this);
}

service::~service()
{
    delete ui;
}

void service::on_facilityreservation_clicked()
{
    this->close();
    facilityreservation *fac=new facilityreservation;
    fac->show();

}

