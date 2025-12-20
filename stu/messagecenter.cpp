#include "messagecenter.h"
#include "ui_messagecenter.h"

MessageCenter::MessageCenter(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MessageCenter)
{
    ui->setupUi(this);
}

MessageCenter::~MessageCenter()
{
    delete ui;
}
