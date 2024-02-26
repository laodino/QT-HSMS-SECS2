#include "hsmssecs2.h"
#pragma execution_character_set("utf-8")
HSMSSECS2::HSMSSECS2()
{
    hsms = new HSMS();
}

void HSMSSECS2::initSetting(const unsigned int t3,
                            const unsigned int t5,
                            const unsigned int t6,
                            const unsigned int t7,
                            const unsigned int t8,
                            const QString local_ip,
                            const unsigned short local_port,
                            const uint16_t device_id)
{
    qDebug()<<"init cfg";
    SECS_CFG sc = {
        t3,
        t5,
        t6,
        t7,
        t8,
        0,
        local_ip,
        local_port,
        device_id
    };
     qDebug()<<"start listen";
    hsms->createConnection(sc);
}
