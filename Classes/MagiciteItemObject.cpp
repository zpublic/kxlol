#include "MagiciteItemObject.h"

USING_NS_CC;

MagiciteItemObject::MagiciteItemObject()
{

}

MagiciteItemObject::~MagiciteItemObject()
{

}

bool MagiciteItemObject::init()
{
    if (!MagiciteGameObject::init())
    {
        return false;
    }
    return true;
}

bool MagiciteItemObject::initWithFile(const char* filename)
{
    if (!MagiciteGameObject::initWithFile(filename))
    {
        return false;
    }
    return true;
}