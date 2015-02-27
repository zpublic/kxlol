#ifndef __MAGICITE_ITEM_COIN__
#define __MAGICITE_ITEM_COIN__

#include "cocos2d.h"
#include "MagiciteTempItem.h"

class MagiciteItemCoin : public MagiciteTempItem
{
public:
    enum : int
    {
        life = 1,
    };

    static std::string name;

    MagiciteItemCoin();
    ~MagiciteItemCoin();

    virtual MagiciteItemObject* getItemObject();
};

#endif //__MAGICITE_ITEM_COIN__