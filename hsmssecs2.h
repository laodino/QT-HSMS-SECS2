#ifndef HSMSSECS2_H
#define HSMSSECS2_H

#include "hsms.h"


class HSMSSECS2:public QObject
{
    Q_OBJECT



public:
    HSMSSECS2();
    /**
     * @brief initSetting
     * @param t3 t3超时 Reply timeout.
     *  范围1-120 每1检测一次 典型值45 单位秒
     * @param t5 t5超时 Connection Separation Timeout.
     * 范围1-240 每1检测一次 典型值10 单位秒
     * @param t6 t6超时  Control Transaction Timeout.
     * 范围1-240 每1检测一次 典型值5 单位秒
     * @param t7 t7超时 Time which a TCP/IP connection can remain in NOT SELECTED state
     *范围1-240 每1检测一次 典型值10 单位秒
     * @param t8 t8超时 Maximum time between successive bytes of a single HSMS message
     *  which may expire before it is considered a communications failure.
     * 范围1-120 每1检测一次 典型值5 单位秒
     * @param local_port 本地端口
     * @param device_id  设备号
     */
    void initSetting(
            const   unsigned int   t3,
            const   unsigned int   t5,
            const   unsigned int   t6,
            const   unsigned int   t7,
            const   unsigned int   t8,
            const   QString local_ip,
            const   unsigned short local_port,
            const   uint16_t device_id
            );

private:
    HSMS * hsms ;
};

#endif // HSMSSECS2_H
