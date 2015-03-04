#include "MagiciteItemCoin.h"
std::string MagiciteItemCoin::name = "Coin";

USING_NS_CC;

MagiciteItemCoin::MagiciteItemCoin()
:MagiciteTempItem(life)
{
    setItemName(name);
}

MagiciteItemCoin::~MagiciteItemCoin()
{

}

bool MagiciteItemCoin::init()
{
    if (!MagiciteTempItem::initWithFile("img\\Magicite\\Item\\coin.png"))
    {
        return false;
    }
    return true;
}

MagiciteItem* MagiciteItemCoin::clone()
{
    return create();
}