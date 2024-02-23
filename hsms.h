#ifndef HSMS_H
#define HSMS_H


#include <QDebug>
#include <QTimer>
#include <QtGlobal>
#include <QTime>
#include "tcp.h"
#include "hsmsmessage.h"


/**
* @projectName   HSMSTEST
* @brief         摘要
* @author        Laodino
* @date          2021-12-16
*/

struct SECS_CFG
{
    unsigned int   t3;			       // reply timeout. (in millisecond, the same below)
    unsigned int   t5;			       // connection separation timeout
    unsigned int   t6;			       // control transaction timeout
    unsigned int   t7;			       // not selected (connection idle) timeout
    unsigned int   t8;			       // network inter-character timeout

    unsigned int   link_test_interval; // in msec, 0 means disabled

    unsigned short local_port;

    unsigned short device_id;          //设备号
};

enum MessageType
{
    DATA        = 0x00,
    SELECTREQ   = 0x01,
    SELECTRSP   = 0x02,
    DESELECTREQ = 0x03,
    DESELECTRSP = 0x04,
    LINKTESTREQ = 0x05,
    LINKTESTRSP = 0x06,
    REJECTREQ   = 0x07,
    SEPARATEREQ = 0x09,
    InValid
};

/**
 * @brief The SelectType enum
 * 选择状态
 */
enum SelectType
{
    COMMUNICATIONESTABLISHED   = 0x00,
    COMMUNICATIONALREADYACTIVE = 0x01,
    CONNECTIONNOTREADY= 0x02,
    CONNECTEXHAUST  = 0x03
};

enum DeSelectType
{
   COMMUNICATIONENDED           = 0x00,
   COMMUNICATIONNOTESTABLISHED  = 0x01,
   COMMUNICATIONBUSY            = 0x02
};

enum HSMSState{
    NOTCONNECTED = 0x01,
    NOTSELECTED = 0x02,
    SELECTED = 0x03
};

class HSMS:public QObject
{
    Q_OBJECT

private:
    TCP *tcp;

    uint32_t systemByte = 0;

    void initConnect();

    void receiveData(QByteArray data);

    HSMSState current_state = HSMSState::NOTCONNECTED;


    void DataProcess(QByteArray &messagedata);

    void SelectReq();

    /**
  * @brief SelectRsp
  * @param sessionid
  * @param messageid
  */
    void SelectRsp(uint16_t sessionid, uint8_t selectstatus, uint32_t messageid);

    /**
  * @brief UnselectReq
  */
    void DeselectReq();
    /**
  * @brief UnselectRsp
  * @param sessionid
  * @param messageid
  */
    void DeselectRsp(uint16_t sessionid, uint8_t deselectstatus, uint32_t messageid);


    void LinkTestReq();

    void LinkTestRsp(uint32_t messageid);
    /**
  * @brief RejectReq
  * @param sessionid
  * @param hb2
  * Ptype不支持，为被拒绝消息的Ptype
  * Stype不支持，为被拒消息的Stype
  * @param hb3
  *拒绝原因
   *   1 Stype不支持
   *  2 Ptype不支持
    *  3 通讯未打开，收到没有匹配的请求消息的回复消息
     * 4 未Selected 收到data
     * 4-127 子标准定义
     * 128-255 预留
    * @param messageid
    */
    void RejectReq(uint16_t sessionid,uint8_t hb2,uint8_t hb3, uint32_t messageid);

    void SeparateReq();

signals:
   void receiveSnFnMessage(HSMSMessage &data);

public:
    HSMS();
    bool createConnection(const SECS_CFG &sc);
    
    void HSMSSendMessage(const QByteArray &data);
};



#endif // HSMS_H
