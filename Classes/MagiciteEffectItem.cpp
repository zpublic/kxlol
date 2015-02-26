#include "MagiciteEffectItem.h"

MagiciteEffectItem::MagiciteEffectItem()
{

}

MagiciteEffectItem::~MagiciteEffectItem()
{

}

void MagiciteEffectItem::positive(MagiciteGameObject* obj)
{
    _effect->positive(obj);
}
