#ifndef __MAGICITE_FOREVER_ITEM__
#define __MAGICITE_FOREVER_ITEM__

#include "MagiciteEffectItem.h"

class MagiciteForeverItem : public MagiciteEffectItem
{
public:
    MagiciteForeverItem();
    ~MagiciteForeverItem();

    virtual void positive();
};

#endif //__MAGICITE_FOREVER_ITEM__