#include "MagiciteItemCoinObject.h"

USING_NS_CC;

MagiciteItemCoinObject::MagiciteItemCoinObject()
{

}

MagiciteItemCoinObject::~MagiciteItemCoinObject()
{

}

bool MagiciteItemCoinObject::init()
{
    if (!MagiciteItemObject::initWithFile("img\\Magicite\\Item\\coin.png"))
    {
        return false;
    }
    return true;
}