#include "itemglobal.h"


QByteArray ItemTypeSpace::List::InitialList(int length)
{
    QByteArray dataheader = ItemType::EnCodeItem(ItemType::List,length);
    return dataheader;
}

QByteArray ItemTypeSpace::Binary::Initial(QByteArray data, int length)
{
    QByteArray dataheader =ItemType::EnCodeItem(ItemType::Binary,length);
    dataheader.append(data);
    qDebug()<<"fulldata"<<dataheader;
    return dataheader;
}

QByteArray ItemTypeSpace::Boolen::Initial(bool data)
{
    QByteArray dataheader =ItemType::EnCodeItem(ItemType::Boolen,1);
    if(data)
        dataheader.append(QByteArray::fromHex(QString("%1").arg(0x01,2,16,QLatin1Char('0')).toUtf8()));
    else
        dataheader.append(QByteArray::fromHex(QString("%1").arg(0x00,2,16,QLatin1Char('0')).toUtf8()));
    return dataheader;
}

QByteArray ItemTypeSpace::ASCII::Initial(QByteArray data)
{
    QByteArray dataheader =ItemType::EnCodeItem(ItemType::ASCII,data.size());
    dataheader.append(data);
    return dataheader;
}

QByteArray ItemTypeSpace::JIS8::Initial(QByteArray data,int length)
{
   QByteArray dataheader =ItemType::EnCodeItem(ItemType::JIS8,length);
   dataheader.append(data);
   return dataheader;
}

QByteArray ItemTypeSpace::C2::Initial(QByteArray data,int length)
{
    QByteArray dataheader =ItemType::EnCodeItem(ItemType::C2,length);
    dataheader.append(data);
    return dataheader;

}

QByteArray ItemTypeSpace::I8::Initial(int8_t data)
{
    QByteArray dataheader =ItemType::EnCodeItem(ItemType::I8,1);
    dataheader.append(data);
    return dataheader;
}

void ItemTypeSpace::I1::Initial()
{

}

void ItemTypeSpace::I2::Initial()
{

}

void ItemTypeSpace::I4::Initial()
{

}

void ItemTypeSpace::F8::Initial()
{

}

void ItemTypeSpace::F4::Initial()
{

}

void ItemTypeSpace::UI8::Initial()
{

}

void ItemTypeSpace::UI1::Initial()
{

}

void ItemTypeSpace::UI2::Initial()
{

}

void ItemTypeSpace::UI4::Initial()
{

}

QByteArray ItemType::EnCodeItem(ItemTypes itemtype, int length)
{

    sizeoflength sizelength;
    if(length<(1<<8))
        sizelength = OneByte;
    else if(length<(1<<16))
        sizelength = TwoBytes;
    else if(length<(1<<24))
        sizelength = ThreeBytes;

    QByteArray data;
    data.append(QByteArray::fromHex(QString("%1").arg((itemtype|sizelength),2,16,QLatin1Char('0')).toUtf8()));
    data.append(QByteArray::fromHex(QString("%1").arg(length,2,16,QLatin1Char('0')).toUtf8()));
    qDebug()<<itemtype<<sizelength<<"header"<<data;
    return data;
}
