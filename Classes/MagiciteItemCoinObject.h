#ifndef __MAGICITE_ITEM_COIN_OBJECT__
#define __MAGICITE_ITEM_COIN_OBJECT__

#include "cocos2d.h"
#include "MagiciteItemObject.h"

class MagiciteItemCoinObject : public MagiciteItemObject
{
public:
    MagiciteItemCoinObject();
    ~MagiciteItemCoinObject();

    virtual bool init();
    CREATE_FUNC(MagiciteItemCoinObject);

};

#endif //__MAGICITE_ITEM_COIN_OBJECT__