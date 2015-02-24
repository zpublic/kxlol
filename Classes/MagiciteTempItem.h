#ifndef __MAGICITE_TEMP_ITEM__
#define __MAGICITE_TEMP_ITEM__

#include "MagiciteEffectItem.h"

class MagiciteTempItem : public MagiciteEffectItem
{
public:
    MagiciteTempItem(int life);
    ~MagiciteTempItem();

    //MagiciteEffectItem
    virtual void positive();

private:
    int                             _life;
};

#endif //__MAGICITE_TEMP_ITEM__