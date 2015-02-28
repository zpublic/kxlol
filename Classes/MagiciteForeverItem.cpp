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
    _effect->positive(obj);
}