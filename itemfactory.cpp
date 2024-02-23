#include "itemfactory.h"

ItemFactory::ItemFactory()
{

}

ItemBase *ItemFactory::CreateNewGEMItem(ItemType::ItemTypes types)
{
    ItemBase * _tempitembase = NULL;
    switch(types)
    {
    case ItemType::List:
        _tempitembase = new ItemTypeSpace::List();
        break;
    case  ItemType::Binary:
        _tempitembase = new ItemTypeSpace::Binary();
        break;
    case ItemType::Boolen:

        break;
    case ItemType::ASCII:

        break;
    case ItemType::JIS8:
        break;
    case ItemType::C2:
        break;
    case ItemType::I8:
        break;
    case ItemType::I1:
        break;
    case ItemType::I2:
        break;
    case ItemType::I4:
        break;
    case ItemType::F8:
        break;
    case ItemType::F4:
        break;
    case ItemType::UI8:
        break;
    case ItemType::UI1:
        break;
    case ItemType::UI2:
        break;
    case ItemType::UI4:
        break;

    }
    return _tempitembase;

}

QByteArray ItemFactory::CreateGEMItemList(int length)
{

    return ItemFactory::CreateNewGEMItem(ItemType::List)->InitialList(length);
}

QByteArray ItemFactory::CreateGEMItemBinary(QByteArray data, int length)
{
    return ItemFactory::CreateNewGEMItem(ItemType::Binary)->Initial(data,length);
}
