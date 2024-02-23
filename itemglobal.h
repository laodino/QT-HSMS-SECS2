#ifndef ITEMGLOBAL_H
#define ITEMGLOBAL_H
#include "itembase.h"
#include <QDebug>
namespace ItemType {


enum  ItemTypes
{
    List   = 0x00,
    Binary = 0x20,
    Boolen = 0x24,
    ASCII  = 0x40,
    JIS8   = 0x44,
    C2     = 0x48,
    I8     = 0x60,
    I1     = 0x64,
    I2     = 0x68,
    I4     = 0x70,
    F8     = 0x80,
    F4     = 0x90,
    UI8    = 0xA0,
    UI1    = 0xA4,
    UI2    = 0xA8,
    UI4    = 0xB0
};

enum sizeoflength
{
    OneByte   =1,
    TwoBytes   =2,
    ThreeBytes =3
};

QByteArray EnCodeItem(ItemTypes itemtype,int length);

}
namespace ItemTypeSpace
{

/**itemstruct
 *  header   1  000000  00
 *             itemtype 长度的字节数 比如1 代表下面1行为item的长度，长度代表itembody的长度
 *  length   2  00000000   长度
 *  length   3  00000000  如果为2
 *  length   4  00000000  如果为3
 *           5 itembody
 *           6 body
 * 实际item长度为 数据长度加上2，3，4
 */


class List: public ItemBase
{
public:
    List()
    {}

     QByteArray InitialList(int length);
};

class  Binary: public ItemBase
{
public:
     Binary() {}
     QByteArray Initial(QByteArray data,int length);
};

class Boolen:public ItemBase
{
public:
    Boolen() {}
    QByteArray Initial(bool data);
};

class ASCII:public ItemBase
{
public:
    ASCII() {}
    QByteArray Initial(QByteArray data);
};

class JIS8:public ItemBase
{
public:
    JIS8() {}
    QByteArray Initial(QByteArray data,int length);
};

class C2:public ItemBase
{
public:
    C2() {}
    QByteArray Initial(QByteArray data,int length);
};

class I8:public ItemBase
{
public:
    I8() {}
    QByteArray Initial(int8_t data);
};

class I1:public ItemBase
{
public:
    I1() {}
    void Initial();
};
class I2:public ItemBase
{
public:
    I2() {}
    void Initial();
};

class I4:public ItemBase
{
public:
    I4() {}
    void Initial();
};

class F8:public ItemBase
{
public:
    F8() {}
    void Initial();
};

class F4:public ItemBase
{
public:
    F4() {}
    void Initial();
};

class UI8:public ItemBase
{
public:
    UI8() {}
    void Initial();
};

class UI1:public ItemBase
{
public:
    UI1() {}
    void Initial();
};

class UI2:public ItemBase
{
public:
    UI2() {}
    void Initial();
};

class UI4:public ItemBase
{
public:
    UI4() {}
    void Initial();
};


}



#endif // ITEMGLOBAL_H
