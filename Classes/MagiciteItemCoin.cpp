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

MagiciteGameObject* MagiciteItemCoin::getItemObject()
{
    return MagiciteItemCoinObject::create();
}

bool MagiciteItemCoin::init()
{
    return true;
}

MagiciteItemCoin* MagiciteItemCoin::create()
{
    auto ptr = new MagiciteItemCoin();
    if (ptr && ptr->init())
    {
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}