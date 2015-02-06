#include "MagiciteGameObject.h"

USING_NS_CC;

MagiciteGameObject::MagiciteGameObject(Type type /* = T_Ground*/)
:ObjType(type)
{

}

MagiciteGameObject* MagiciteGameObject::create(const char* filename)
{
    auto ptr = new MagiciteGameObject();
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

bool MagiciteGameObject::init()
{
    if (!MagiciteGamePhySprite::init())
    {
        return false;
    }
    return true;
}

bool MagiciteGameObject::initWithFile(const char* filename)
{
    if (!MagiciteGamePhySprite::initWithFile(filename))
    {
        return false;
    }
    return true;
}

MagiciteGameObject* MagiciteGameObject::create(Type type)
{
    auto ptr = new MagiciteGameObject(type);
    if (ptr && ptr->init())
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