#include "MagiciteItem.h"

MagiciteItem::MagiciteItem()
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

MagiciteItemObject* MagiciteItem::getItemObject()
{
    return nullptr;
}