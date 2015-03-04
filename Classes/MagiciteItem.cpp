#include "MagiciteItem.h"
#include "MagiciteItemObject.h"

std::string MagiciteItem::_name = "item";
int MagiciteItem::_id = 0;

MagiciteItem::MagiciteItem(ItemType type /*= NormalItem*/)
:_itemType(type)
{

}

MagiciteItem::~MagiciteItem()
{

}

std::string MagiciteItem::getItemName() const
{
    return _name;
}

void MagiciteItem::setItemName(const std::string& name)
{
    _name = name;
}

void MagiciteItem::destroy()
{

}

MagiciteGameObject* MagiciteItem::getItemObject()
{
    return nullptr;
}

int MagiciteItem::getItemId() const
{
    return _id;
}

void MagiciteItem::setItemId(int Id)
{
    _id = Id;
}