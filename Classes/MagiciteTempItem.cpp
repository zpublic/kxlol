#include "MagiciteTempItem.h"

MagiciteTempItem::MagiciteTempItem(int life)
:_life(life)
{

}

MagiciteTempItem::~MagiciteTempItem()
{

}

void MagiciteTempItem::positive(MagiciteGameObject* obj)
{
    if (_effect != nullptr)
    {
        MagiciteEffectItem::positive(obj);
        --_life;

        if (_life <= 0)
        {
            this->destroy();
        }
    }
   
}

bool MagiciteTempItem::init()
{
    if (!MagiciteEffectItem::init())
    {
        return false;
    }
    return true;
}

bool MagiciteTempItem::initWithFile(const char* filename)
{
    if (!MagiciteEffectItem::initWithFile(filename))
    {
        return false;
    }
    return true;
}