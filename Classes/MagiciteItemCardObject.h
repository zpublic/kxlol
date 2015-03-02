#ifndef __MAGICITE_ITEM_CARD_OBJECT__
#define __MAGICITE_ITEM_CARD_OBJECT__

#include "cocos2d.h"
#include "MagiciteItemObject.h"

class MagiciteItemCardObject : public MagiciteItemObject
{
public:
    MagiciteItemCardObject();
    ~MagiciteItemCardObject();

    virtual bool init();
    CREATE_FUNC(MagiciteItemCardObject);

};

#endif //__MAGICITE_ITEM_CARD_OBJECT__