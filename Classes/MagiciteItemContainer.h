#ifndef __MAGICITE_ITEM_CONTAINER__
#define __MAGICITE_ITEM_CONTAINER__

#include "cocos2d.h"
#include <vector>

class MagiciteItem;

class MagiciteItemContainer
{
public:
    MagiciteItemContainer(int max_size);
    ~MagiciteItemContainer();

    virtual void addItem(MagiciteItem* item);
    virtual void eraseItem(int id);
    virtual MagiciteItem* getItem(int index);

    void touchEvent(int n);

protected:
    std::vector<std::pair<int, MagiciteItem*>>              _container;
    int                                                     _max_size;
};

#endif //__MAGICITE_ITEM_CONTAINER__