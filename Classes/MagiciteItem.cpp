#include "MagiciteItem.h"

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

int MagiciteItem::getItemId() const
{
    return _id;
}

void MagiciteItem::setItemId(int Id)
{
    _id = Id;
}

bool MagiciteItem::init()
{
    if (!MagiciteGameObject::init())
    {
        return false;
    }
    return true;
}

bool MagiciteItem::initWithFile(const char* filename)
{
    if (!MagiciteGameObject::initWithFile(filename))
    {
        return false;
    }
    return true;
}