#ifndef __MAGICITE_FOREVER_ITEM__
#define __MAGICITE_FOREVER_ITEM__

#include "MagiciteEffectItem.h"

class MagiciteForeverItem : public MagiciteEffectItem
{
public:
    MagiciteForeverItem();
    ~MagiciteForeverItem();

    virtual void positive(MagiciteGameObject* obj);
};

#endif //__MAGICITE_FOREVER_ITEM__