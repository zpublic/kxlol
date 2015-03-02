#include "MagiciteItemCardObject.h"

USING_NS_CC;

MagiciteItemCardObject::MagiciteItemCardObject()
{

}

MagiciteItemCardObject::~MagiciteItemCardObject()
{

}

bool MagiciteItemCardObject::init()
{
    if (!MagiciteItemObject::initWithFile("img\\Magicite\\Item\\card.png"))
    {
        return false;
    }
    return true;
}