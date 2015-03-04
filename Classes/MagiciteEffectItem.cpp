#include "MagiciteEffectItem.h"
#include "MagiciteEffect.h"

MagiciteEffectItem::MagiciteEffectItem()
:MagiciteItem(EffectItem), _effect(nullptr)
{
    
}

MagiciteEffectItem::~MagiciteEffectItem()
{
    CC_SAFE_DELETE(_effect);
}

void MagiciteEffectItem::positive(MagiciteGameObject* obj)
{
    if (_effect != nullptr)
    {
        _effect->positive(obj);
    }
}
