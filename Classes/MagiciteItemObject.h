#ifndef __MAGICITE_ITEM_OBJECT__
#define __MAGICITE_ITEM_OBJECT__

#include "cocos2d.h"
#include "MagiciteGameObject.h"

class MagiciteItemObject : public MagiciteGameObject
{
public:
    MagiciteItemObject();
    ~MagiciteItemObject();

    virtual bool init();
    virtual bool initWithFile(const char* filename);
};

#endif //__MAGICITE_ITEM_OBJECT__