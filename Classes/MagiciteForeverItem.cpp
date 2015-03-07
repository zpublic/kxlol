#include "MagiciteForeverItem.h"

MagiciteForeverItem::MagiciteForeverItem()
{

}

MagiciteForeverItem::~MagiciteForeverItem()
{

}

void MagiciteForeverItem::positive(MagiciteGameObject* obj)
{
    if (_effect != nullptr)
    {
        MagiciteEffectItem::positive(obj);
    }
}

bool MagiciteForeverItem::init()
{
    if (!MagiciteEffectItem::init())
    {
        return false;
    }
    return true;
}

bool MagiciteForeverItem::initWithFile(const char* filename)
{
    if (!MagiciteEffectItem::initWithFile(filename))
    {
        return false;
    }
    return true;
}