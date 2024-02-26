#include "hsmsgem.h"
#include "ui_hsmsgem.h"
#pragma execution_character_set("utf-8")

HSMSGEM::HSMSGEM(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HSMSGEM)
{
    ui->setupUi(this);
    hs = new HSMSSECS2();

}

HSMSGEM::~HSMSGEM()
{
    delete ui;
}






void HSMSGEM::on_pushButton_bulidupconncet_clicked()
{
    buildupConnection();
}

void HSMSGEM::buildupConnection()
{
    unsigned long t3 = ui->lineEdit_t3->text().toULong();
    unsigned long t5 = ui->lineEdit_t5->text().toULong();
    unsigned long t6 = ui->lineEdit_t6->text().toULong();
    unsigned long t7 = ui->lineEdit_t7->text().toULong();
    unsigned long t8 = ui->lineEdit_t8->text().toULong();
    QString ipAddress = ui->lineEdit_localip->text().trimmed();
    unsigned short port = ui->lineEdit_localport->text().toUShort();
    uint16_t deviceID = ui->lineEdit_deviceid->text().toUShort();
    hs->initSetting(t3,t5,t6,t7,t8,ipAddress,port,deviceID);
}
