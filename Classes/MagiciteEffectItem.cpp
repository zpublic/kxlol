#include "MagiciteEffectItem.h"
#include "MagiciteEffect.h"

MagiciteEffectItem::MagiciteEffectItem()
:MagiciteItem(EffectItem), _effect(nullptr), _cool_down(0.0f)
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
        auto nowTime = std::chrono::system_clock::now();
        std::chrono::system_clock::duration deltaTime = nowTime - _last_time;
        if (std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count() > _cool_down * 1000)
        {
            _last_time = nowTime;
            _effect->positive(obj);
        }
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

void MagiciteEffectItem::setCd(long long cd)
{
    _cool_down = cd;
}

long long MagiciteEffectItem::getCd() const
{
    return _cool_down;
}