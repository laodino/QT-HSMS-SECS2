#ifndef HSMSGEM_H
#define HSMSGEM_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>
#include "hsmsgemglobal.h"
#include "itemglobal.h"
#include "qcommunicationstatemachine.h"
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

private:
    Ui::HSMSGEM *ui;

signals:





};

#endif // HSMSGEM_H
