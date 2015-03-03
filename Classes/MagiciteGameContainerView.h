#ifndef __MAGICITE_GAME_CONTAINER_VIEW__
#define __MAGICITE_GAME_CONTAINER_VIEW__

#include "MagiciteGameObject.h"
#include "MagiciteGameControlAble.h"
#include <vector>

class MagiciteItemContainer;
class MagiciteItemObject;
class MagiciteItem;

class MagiciteGameContainerView : public MagiciteGameObject, public MagiciteGameControlAble
{
public:
    MagiciteGameContainerView();
    ~MagiciteGameContainerView();


    virtual void addItem(MagiciteItem* item) = 0;
    virtual void eraseItem(int num) = 0;

    void ItemEvent(int n);
 
    //MagiciteGameContralAble
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    virtual bool init(MagiciteGameObject* obj, int max_size);

protected:
    MagiciteItemContainer*                          _container;
    std::vector<MagiciteGameObject*>*               _list;
    MagiciteGameObject*                             _obj;
    int                                             _max_size;
};

#endif //__MAGICITE_GAME_CONTAINER_VIEW__