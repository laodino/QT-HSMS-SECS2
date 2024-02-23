#include "hsmsgem.h"
#include "ui_hsmsgem.h"
#pragma execution_character_set("utf-8")

HSMSGEM::HSMSGEM(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HSMSGEM)
{
    ui->setupUi(this);
}

HSMSGEM::~HSMSGEM()
{
    delete ui;
}





