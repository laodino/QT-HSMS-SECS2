#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <stdint.h>
#include "itemglobal.h"
#include "itembase.h"
class ItemFactory
{
public:
    ItemFactory();
    static  ItemBase* CreateNewGEMItem(ItemType::ItemTypes types);
   static QByteArray CreateGEMItemList(int length);

   static QByteArray CreateGEMItemBinary(QByteArray data,int length);
};

#endif // ITEMFACTORY_H
