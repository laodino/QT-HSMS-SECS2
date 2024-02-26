#include "hsms.h"
#pragma execution_character_set("utf-8")

HSMS::HSMS()
{
    tcp = new TCP();
    initConnect();
}

void HSMS::initConnect()
{

    connect(tcp,&TCP::newData,this,&HSMS::receiveData);

    connect(tcp,&TCP::connected,this,[=]{
        //切换当前状态
        current_state = HSMSState::NOTSELECTED;
        //生成随机句柄
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        uint32_t rand = qrand();
        qDebug()<<"rand systembyte"<<rand;
        systemByte = rand;
    });
}

void HSMS::receiveData(QByteArray data)
{
   DataProcess(data);
}

bool HSMS::createConnection(const SECS_CFG &sc)
{
    tcp->listenPort(QHostAddress(sc.local_ip),sc.local_port);
    return true;
}

void HSMS::HSMSSendMessage(const QByteArray &data)
{
    
}

void HSMS::DataProcess(QByteArray &messagedata)
{
    //超时处理
    //todo！
    HSMSMessage  newmessage ;
    if(!newmessage.fromByteArray(messagedata)){
        qDebug()<<"HSMS消息格式错误！";
        return;
    }
    qDebug()<<"收到新消息:\r\n"
          <<newmessage;
    switch(newmessage.getStype())
    {
    case DATA:
        //DECODE SnFn;
        qDebug()<<"收到SnFn指令";
        emit receiveSnFnMessage(newmessage);
        break;
    case SELECTREQ:
    {
        //selectreq
        qDebug()<<"收到SelectReq指令";
        SelectType st ;
        //匹配当前状态
        switch (current_state) {
        case HSMSState::SELECTED:
            st = SelectType::COMMUNICATIONALREADYACTIVE;
            break;
        case HSMSState::NOTSELECTED:
            st = SelectType::COMMUNICATIONESTABLISHED;
            break;
        case HSMSState::NOTCONNECTED:
            st = SelectType::CONNECTIONNOTREADY;
            break;
        }
        qDebug()<<"systembytes"<<QString("%1").arg(newmessage.getSystemByte(),8,16,QLatin1Char('0')).toUpper();
        SelectRsp(newmessage.getSessionID(),st,newmessage.getSystemByte());
        break;
    }
    case SELECTRSP:
        qDebug()<<"收到SelectRsp指令";

        // test the link
        //WriteSocket(LinkTestRsp(newmessage.SystemBytes));
        break;
    case DESELECTREQ:
    {
        qDebug()<<"收到DESelectReq指令";
        DeSelectType st;
        //匹配当前状态
        switch (current_state) {
        case HSMSState::SELECTED:
            current_state = HSMSState::NOTSELECTED;
            st = DeSelectType::COMMUNICATIONENDED;
            break;
        case HSMSState::NOTSELECTED:
            st = DeSelectType::COMMUNICATIONNOTESTABLISHED;
            break;
        case HSMSState::NOTCONNECTED:
            st = DeSelectType::COMMUNICATIONNOTESTABLISHED;
            break;
        }
        DeselectRsp(newmessage.getSessionID(),st,newmessage.getSystemByte());
        break;
    }
    case DESELECTRSP:
        qDebug()<<"收到DeSelectedRsp指令";
        current_state = HSMSState::NOTSELECTED;
        break;
    case LINKTESTREQ:
        qDebug()<<"收到LinkTestReq指令";
        //testlink
        LinkTestRsp(newmessage.getSystemByte());
        //linkTestTimer->start();
        break;
    case LINKTESTRSP:
        qDebug()<<"收到LinkTestRsp指令";

        break;
    case REJECTREQ:
        qDebug()<<"收到RejectedReq指令";
        /*   1 Stype不支持
         *  2 Ptype不支持
         *  3 通讯未打开，收到没有匹配的请求消息的回复消息
         * 4 未Selected 收到data
         * 4-127 子标准定义
         * 128-255 预留
         */
        break;
    case SEPARATEREQ:
        qDebug()<<"收到SepearteReq指令";
        //强制断开HSMS，不断开TCP，相当于无理由的Deselect
       current_state = HSMSState::NOTSELECTED;
        break;
    default:
        //invalidmessage
        RejectReq(newmessage.getSessionID(),newmessage.getStype(),0x01,newmessage.getSystemByte());
    }
}


void  HSMS::SelectReq()
{
    qDebug()<<"SelectReq";
    //00 00 00 0a ff ff 00 00 00 01 00 00 00 01
    HSMSMessage *hm = new HSMSMessage();
    hm->setData(0xFFFF,0x00,0x00,0x00,0x01,systemByte,NULL);
    qDebug()<< *hm;
    tcp->WriteSocket(hm->data());
    delete hm;
}

void  HSMS::SelectRsp(uint16_t sessionid,uint8_t selectstatus, uint32_t messageid)
{
    qDebug()<<"SelectRsp";
    //00 00 00 0a ff ff 00 00 00 02 00 00 00 0?
    HSMSMessage *hm = new HSMSMessage();
    hm->setData(sessionid,0x00,selectstatus,0x00,0x02,messageid,NULL);
    qDebug()<< *hm;
    tcp->WriteSocket(hm->data());
    delete hm;
}

void HSMS::DeselectReq()
{
    //00 00 00 0a ff ff 00 00 00 03 00 00 00 0?
    HSMSMessage *hm = new HSMSMessage();
    hm->setData(0xFFFF,0x00,0x00,0x00,0x03,systemByte,NULL);
    qDebug()<< *hm;
    tcp->WriteSocket(hm->data());
    delete hm;
}

void  HSMS::DeselectRsp(uint16_t sessionid,uint8_t deselectstatus,uint32_t messageid)
{
    //00 00 00 0a ff ff 00 00 00 04 00 00 00 0?
    HSMSMessage *hm = new HSMSMessage();
    hm->setData(sessionid,0x00,deselectstatus,0x00,0x04,messageid,NULL);
    qDebug()<< *hm;
    tcp->WriteSocket(hm->data());
    delete hm;
}

void  HSMS::LinkTestReq()
{
    //00 00 00 0a ff ff 00 00 00 05 00 00 00 0?
    HSMSMessage *hm = new HSMSMessage();
    hm->setData(0xFFFF,0x00,0x00,0x00,0x05,systemByte,NULL);
    qDebug()<< hm;
    tcp->WriteSocket(hm->data());
    delete hm;
}

void  HSMS::LinkTestRsp(uint32_t messageid)
{
    //00 00 00 0a ff ff 00 00 00 06 00 00 00 0?
    HSMSMessage *hm = new HSMSMessage();
    hm->setData(0xFFFF,0x00,0x00,0x00,0x06,messageid,NULL);
    qDebug()<< *hm;
    tcp->WriteSocket(hm->data());
    delete hm;
}

void HSMS::RejectReq(uint16_t sessionid,uint8_t hb2,uint8_t hb3, uint32_t messageid)
{
    //00 00 00 0a ff ff 00 00 00 07 00 00 00 0?
    HSMSMessage *hm = new HSMSMessage();
    hm->setData(sessionid,hb2,hb3,0x00,0x07,messageid,NULL);
    qDebug()<< *hm;
    tcp->WriteSocket(hm->data());
    delete hm;
}

void  HSMS::SeparateReq()
{
    //00 00 00 0a ff ff 00 00 00 09 00 00 00 0?
    HSMSMessage *hm = new HSMSMessage();
    hm->setData(0xFFFF,0x00,0x00,0x00,0x09,systemByte,NULL);
    qDebug()<< *hm;
    tcp->WriteSocket(hm->data());
    delete hm;
}

