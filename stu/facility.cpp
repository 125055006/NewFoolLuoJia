#include "facility.h"
#include "ui_facility.h"

facility::facility(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::facility)
{
    ui->setupUi(this);
}

facility::~facility()
{
    delete ui;
}
