#ifndef HSMSGEM_H
#define HSMSGEM_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>
#include "hsmssecs2.h"
#include "itemglobal.h"
#include "itemfactory.h"

/**
* @projectName   HSMSTEST
* @brief         摘要
* @author        Laodino
* @date          2021-12-16
*/
namespace Ui {
class HSMSGEM;
}

class HSMSGEM : public QWidget
{
    Q_OBJECT

public:
    explicit HSMSGEM(QWidget *parent = 0);
    ~HSMSGEM();

private slots:

    void on_pushButton_bulidupconncet_clicked();

private:
    Ui::HSMSGEM *ui;

    HSMSSECS2 *hs;

    void buildupConnection();

signals:





};

#endif // HSMSGEM_H
