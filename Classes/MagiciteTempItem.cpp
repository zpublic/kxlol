#include "MagiciteTempItem.h"

MagiciteTempItem::MagiciteTempItem(int life)
:_life(life)
{

}

MagiciteTempItem::~MagiciteTempItem()
{

}

void MagiciteTempItem::positive()
{
    _effect->positive();
    --_life;

    if (_life <= 0)
    {
        this->destroy();
    }
}
