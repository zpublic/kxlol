#ifndef __MAGICITE_GAME_CONTAINER_VIEW__
#define __MAGICITE_GAME_CONTAINER_VIEW__

#include "MagiciteGameObject.h"
#include "MagiciteGameControlAble.h"
#include <vector>

class MagiciteGameContainerView : public MagiciteGameObject, public MagiciteGameControlAble
{
public:
    MagiciteGameContainerView(int n = _max_size);
    ~MagiciteGameContainerView();

    virtual bool init();

    virtual void addItem(MagiciteGameObject* item) = 0;
    virtual void eraseItem(int num) = 0;
 
    //MagiciteGameContralAble
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    std::function<void(int)>                        _touch_event;

protected:
    std::vector<MagiciteGameObject*>                _list;
    static const int                                _max_size = 9;
};

#endif //__MAGICITE_GAME_CONTAINER_VIEW__