#include "MagiciteEffectItem.h"
#include "MagiciteEffect.h"

MagiciteEffectItem::MagiciteEffectItem()
{
    
}

MagiciteEffectItem::~MagiciteEffectItem()
{
    CC_SAFE_DELETE(_effect);
}

void MagiciteEffectItem::positive(MagiciteGameObject* obj)
{
    _effect->positive(obj);
}
