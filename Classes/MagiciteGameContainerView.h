#ifndef __MAGICITE_GAME_CONTAINER_VIEW__
#define __MAGICITE_GAME_CONTAINER_VIEW__

#include "MagiciteGameObject.h"
#include "MagiciteGameControlAble.h"
#include <vector>

class MagiciteItemContainer;
class MagiciteItem;

class MagiciteGameContainerView : public MagiciteGameObject
{
public:
    MagiciteGameContainerView();
    ~MagiciteGameContainerView();

    virtual void addItem(MagiciteItem* item) = 0;
    virtual void eraseItem(int num) = 0;
    virtual MagiciteItem* getItem(int num);

    virtual bool init(int max_size);

    std::function<void(int)>                                _itemEvent;

protected:
    MagiciteItemContainer*                                  _container;
    std::vector<std::pair<int, MagiciteItem*>>*             _list;
    int                                                     _max_size;
};

#endif //__MAGICITE_GAME_CONTAINER_VIEW__