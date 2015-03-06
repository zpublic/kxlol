#include "MagiciteEffectItem.h"
#include "MagiciteEffect.h"

MagiciteEffectItem::MagiciteEffectItem()
:MagiciteItem(EffectItem), _effect(nullptr)
{
    
}

MagiciteEffectItem::~MagiciteEffectItem()
{
    _effect->release();
}

void MagiciteEffectItem::positive(MagiciteGameObject* obj)
{
    if (_effect != nullptr)
    {
        _effect->positive(obj);
    }
}

bool MagiciteEffectItem::init()
{
    if (!MagiciteItem::init())
    {
        return false;
    }

    return true;
}

bool MagiciteEffectItem::initWithFile(const char* filename)
{
    if (!MagiciteItem::initWithFile(filename))
    {
        return false;
    }
    return true;
}

void MagiciteEffectItem::setEffect(MagiciteEffect* effect)
{
    _effect = effect;
    effect->retain();
}