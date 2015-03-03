#ifndef __MAGICITE_ITEM_BAG__
#define __MAGICITE_ITEM_BAG__

#include "MagiciteItemContainer.h"

class MagiciteGameBagView;
class MagiciteGameObject;

class MagiciteItemBag : public MagiciteItemContainer
{
public:
    MagiciteItemBag(MagiciteGameObject* obj);

};

#endif //__MAGICITE_ITEM_BAG__