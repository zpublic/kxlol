#include "MagiciteGameAmmo.h"

USING_NS_CC;

MagiciteGameAmmo::MagiciteGameAmmo()
:MagiciteGameObject(T_Ammo)
{

}

bool MagiciteGameAmmo::init()
{
    if (!MagiciteGameObject::init())
    {
        return false;
    }
    return true;
}

bool MagiciteGameAmmo::initWithFile(const char* filename)
{
    if (!MagiciteGameObject::initWithFile(filename))
    {
        return false;
    }
    return true;
}

MagiciteGameAmmo* MagiciteGameAmmo::create(const char* filename)
{
    auto ptr = new MagiciteGameAmmo();
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