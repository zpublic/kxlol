#include "MagiciteItemCoin.h"

USING_NS_CC;

MagiciteItemCoin::MagiciteItemCoin()
{

}

MagiciteItemCoin::~MagiciteItemCoin()
{

}

bool MagiciteItemCoin::init()
{
    if (!MagiciteItemObject::initWithFile("img\\Magicite\\Item\\coin.png"))
    {
        return false;
    }
    return true;
}