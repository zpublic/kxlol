#include "MagiciteTempItem.h"
#include "MagiciteEffect.h"

MagiciteTempItem::MagiciteTempItem(int life)
:_life(life)
{

}

MagiciteTempItem::~MagiciteTempItem()
{

}

void MagiciteTempItem::positive(MagiciteGameObject* obj)
{
    _effect->positive(obj);
    --_life;

    if (_life <= 0)
    {
        this->destroy();
    }
}
