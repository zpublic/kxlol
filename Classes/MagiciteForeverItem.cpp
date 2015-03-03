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