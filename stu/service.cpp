#include "service.h"
#include "ui_service.h"
#include"facilityreservation.h"
#include"facility.h"
#include"campusinfowidget.h"
#include"SchoolCalendarWidget.h"
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

    facilityreservation *fac=new facilityreservation;
    fac->show();

}


void service::on_telephone_clicked()
{

    facility *fa=new facility;
    fa->show();
}


void service::on_pushButton_clicked()
{

    CampusInfoWidget *cam=new CampusInfoWidget;
    cam->show();
}


void service::on_pushButton_2_clicked()
{
    widgetCalendar*wid=new widgetCalendar;
    wid->show();
}

