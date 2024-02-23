#ifndef ITEMBASE_H
#define ITEMBASE_H
#include <QDebug>
#include <stdint.h>

class ItemBase
{
public:
    ItemBase();
    virtual QByteArray InitialList(int length);
    virtual QByteArray Initial(QByteArray data,int length);
    virtual QByteArray Initial(bool data);
    virtual QByteArray Initial(QByteArray data);
    virtual QByteArray Initial(float data);
    virtual QByteArray Initial(double data);

    virtual QByteArray Initial(uint8_t data);
    virtual QByteArray Initial(uint16_t data);
    virtual QByteArray Initial(uint32_t data);
    virtual QByteArray Initial(uint64_t data);
    virtual QByteArray Initial(int8_t data);
    virtual QByteArray Initial(int16_t data);
    virtual QByteArray Initial(int32_t data);
    virtual QByteArray Initial(int64_t data);

};

#endif // ITEMBASE_H
