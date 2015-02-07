#include "MagiciteGamePitfall.h"

USING_NS_CC;

MagiciteGamePitfall::MagiciteGamePitfall()
:MagiciteGameObject(MagiciteGameObject::T_Pitfall),_is_active(true), _change_flag(false)
{

}

bool MagiciteGamePitfall::init()
{
    if (!MagiciteGameObject::init())
    {
        return false;
    }
    return true;
}

bool MagiciteGamePitfall::initWithFile(const char* filename)
{
    if (!MagiciteGameObject::initWithFile(filename))
    {
        return false;
    }
    return true;
}

MagiciteGamePitfall* MagiciteGamePitfall::create(const char* filename)
{
    auto ptr = new MagiciteGamePitfall();
    if (ptr && ptr->initWithFile(filename))
    {
        ptr->autorelease();
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

bool MagiciteGamePitfall::getPitFallAvtive() const
{
    return _is_active;
}

void MagiciteGamePitfall::setPitFallAvtive(bool is_active)
{
    if (is_active != _is_active)
    {
        _is_active = is_active;
        _change_flag = true;
    }
}

bool MagiciteGamePitfall::getChangeFlag() const
{
    return _change_flag;
}

void MagiciteGamePitfall::setChangeFlag(bool flag)
{
    _change_flag = flag;
}