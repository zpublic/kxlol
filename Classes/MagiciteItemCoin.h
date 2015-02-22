#ifndef __MAGICITE_ITEM_COIN__
#define __MAGICITE_ITEM_COIN__

#include "cocos2d.h"
#include "MagiciteItemObject.h"

class MagiciteItemCoin : public MagiciteItemObject
{
public:
    MagiciteItemCoin();
    ~MagiciteItemCoin();

    virtual bool init();
    CREATE_FUNC(MagiciteItemCoin);

};

#endif //__MAGICITE_ITEM_COIN__