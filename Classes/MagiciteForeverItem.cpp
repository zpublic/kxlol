#include "MagiciteForeverItem.h"
#include "MagiciteEffect.h"

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
        _effect->positive(obj);
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