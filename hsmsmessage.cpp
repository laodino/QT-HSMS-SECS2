#include "hsmsmessage.h"
#pragma execution_character_set("utf-8")
HSMSMessage::HSMSMessage()
{

}

HSMSMessage::~HSMSMessage()
{

}

QByteArray HSMSMessage::data()
{
    //如果是SnFn，不是事务
    if(SType==0)
    {
        //sessionID由方向和设备ID组成
        SessionID = (Direction&0x8000)|(EquipID&0x7FFF);
        //Headerbyte2由wbit和stream组成
        HeaderByte2 = (WBit&0x80)|(Stream&0x7F);
    }
    MessageLength = 10+MessageText.size();
    //arg第二个参数filedwidth，转为16进制需要乘2
    QByteArray messageByteArray;
    messageByteArray.append(QByteArray::fromHex(QString("%1").arg(MessageLength,8,16,QLatin1Char('0')).toUtf8()));
    messageByteArray.append(QByteArray::fromHex(QString("%1").arg(SessionID,4,16,QLatin1Char('0')).toUtf8()));
    messageByteArray.append(QByteArray::fromHex(QString("%1").arg(HeaderByte2,2,16,QLatin1Char('0')).toUtf8()));
    messageByteArray.append(QByteArray::fromHex(QString("%1").arg(HeaderByte3,2,16,QLatin1Char('0')).toUtf8()));
    messageByteArray.append(QByteArray::fromHex(QString("%1").arg(PType,2,16,QLatin1Char('0')).toUtf8()));
    messageByteArray.append(QByteArray::fromHex(QString("%1").arg(SType,2,16,QLatin1Char('0')).toUtf8()));
    messageByteArray.append(QByteArray::fromHex(QString("%1").arg(SystemBytes,8,16,QLatin1Char('0')).toUtf8()));
    messageByteArray.append(MessageText);
    qDebug()<<"HSMSMessageData:"<<messageByteArray.toHex().toUpper();
    return messageByteArray;
}

bool HSMSMessage::fromByteArray(QByteArray messageByteArray)
{
    QDataStream mlen(messageByteArray.left(4));
    mlen>>MessageLength;

    qDebug()<<messageByteArray.size()<<MessageLength;
    //这里不包含前四位消息长度
    if(messageByteArray.size()<14||(messageByteArray.size()-4)!=MessageLength)
        return false;

    QDataStream msid(messageByteArray.mid(4,2));
    msid>>SessionID;
    QDataStream mh2(messageByteArray.mid(6,1));
    mh2>>HeaderByte2;
    QDataStream mh3(messageByteArray.mid(7,1));
    mh3>>HeaderByte3;
    QDataStream mpt(messageByteArray.mid(8,1));
    mpt>>PType;
    QDataStream mst(messageByteArray.mid(9,1));
    mst>>SType;
    QDataStream msb(messageByteArray.mid(10,4));
    msb>>SystemBytes;
    MessageText = messageByteArray.mid(14);
    //处理非事务情况
    if(SType==0){
        Direction = SessionID>>15;
        EquipID = SessionID&0x7FFF;

        WBit = HeaderByte2>>7;
        Stream = HeaderByte2&0x7F;
    }
    return true;
}

void HSMSMessage::setData(const uint16_t SID,const uint8_t HB2,const uint8_t HB3,const uint8_t PT,const uint8_t ST,const uint32_t SB,const QByteArray &MT)
{
    SessionID = SID;
    HeaderByte2 = HB2;
    HeaderByte3 = HB3;
    PType = PT;
    SType = ST;
    SystemBytes =SB;
    MessageText = MT;
   qDebug()<<"SetData"
    <<"SessionID"<<SessionID
    <<"HeaderByte2"<<HeaderByte2
    <<"HeaderByte3"<<HeaderByte3
    <<"PType"<<PType
    <<"SType"<<SType
    <<"SystemBytes"<<SystemBytes
    <<"MessageText"<<MessageText;
}

uint8_t HSMSMessage::getStype()
{
    return SType;
}

uint16_t HSMSMessage::getSessionID()
{
    return SessionID;
}

uint32_t HSMSMessage::getSystemByte()
{
    return SystemBytes;
}

QDebug operator<<(QDebug dbg,const HSMSMessage &hm)
{
    QDebugStateSaver stateSaver(dbg);
    dbg
    <<"MessageLength:"<<QString("%1").arg(hm.MessageLength,8,16,QLatin1Char('0')).toUtf8()<<"\r\n"
    <<"SessionID"<<QString("%1").arg(hm.SessionID,4,16,QLatin1Char('0')).toUtf8()<<"\r\n"
    <<"HeaderByte2"<<QString("%1").arg( hm.HeaderByte2,2,16,QLatin1Char('0')).toUtf8()<<"\r\n"
    <<"HeaderByte3"<<QString("%1").arg( hm.HeaderByte3,2,16,QLatin1Char('0')).toUtf8()<<"\r\n"
    <<"PType"<<QString("%1").arg( hm.PType,2,16,QLatin1Char('0')).toUtf8()<<"\r\n"
    <<"SType"<<QString("%1").arg( hm.SType,2,16,QLatin1Char('0')).toUtf8()<<"\r\n"
    <<"SystemBytes"<<QString("%1").arg( hm.SystemBytes,8,16,QLatin1Char('0')).toUtf8()<<"\r\n"
    <<"MessageText"<<hm.MessageText;
    return dbg;
}
