#ifndef __MAGICITE_GAME_CONTROL_ABLE__
#define __MAGICITE_GAME_CONTROL_ABLE__

#include "cocos2d.h"

class MagiciteGameControlAble
{
public:
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) = 0;
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) = 0;

    static void dispatchKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event, MagiciteGameControlAble *controlable);
    static void dispatchKeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event, MagiciteGameControlAble *controlable);
};

#endif //__MAGICITE_GAME_CONTROL_ABLE__