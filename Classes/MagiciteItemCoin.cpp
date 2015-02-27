#include "MagiciteItemCoin.h"
#include "MagiciteItemCoinObject.h"
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

MagiciteItemObject* MagiciteItemCoin::getItemObject()
{
    return MagiciteItemCoinObject::create();
}
