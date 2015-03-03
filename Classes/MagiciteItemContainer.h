#ifndef __MAGICITE_ITEM_CONTAINER__
#define __MAGICITE_ITEM_CONTAINER__

#include "cocos2d.h"
#include <vector>

class MagiciteItem;
class MagiciteGameObject;
class MagiciteGameContainerView;

class MagiciteItemContainer
{
public:
    MagiciteItemContainer(MagiciteGameObject* obj);
    ~MagiciteItemContainer();

    virtual void addItem(MagiciteItem* item);
    virtual void eraseItem(int id);
    virtual MagiciteItem* getItem(int id);

    void touchEvent(int n);

    void bindView(MagiciteGameContainerView* view);
protected:
    std::vector<std::pair<int, MagiciteItem*>>              _container;
    MagiciteGameContainerView*                              _view;
    MagiciteGameObject*                                     _obj;
    static const int                                        _max_size = 9;
};

#endif //__MAGICITE_ITEM_CONTAINER__