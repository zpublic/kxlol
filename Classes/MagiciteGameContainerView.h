#ifndef __MAGICITE_GAME_CONTAINER_VIEW__
#define __MAGICITE_GAME_CONTAINER_VIEW__

#include "MagiciteGameObject.h"
#include "MagiciteGameControlAble.h"
#include <vector>

class MagiciteItemContainer;
class MagiciteItem;

class MagiciteGameContainerView : public MagiciteGameObject, public MagiciteGameControlAble
{
public:
    MagiciteGameContainerView();
    ~MagiciteGameContainerView();

    void addItem(MagiciteItem* item, std::vector<std::pair<int, MagiciteItem*>>::iterator iter);
    void eraseItem(std::vector<std::pair<int, MagiciteItem*>>::iterator iter);
    virtual MagiciteItem* getItem(int num);

    virtual bool init(int max_size);

    void setViewInvisible(bool);
    bool getViewInvisible() const;

    std::function<void(int)>                                _itemEvent;
    virtual void onItemUse(int id);

    //MagiciteGameControlAble
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

protected:
    MagiciteItemContainer*                                  _container;
    std::vector<std::pair<int, MagiciteItem*>>*             _list;
    int                                                     _max_size;
};

#endif //__MAGICITE_GAME_CONTAINER_VIEW__