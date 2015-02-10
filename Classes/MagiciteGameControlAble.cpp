#include "MagiciteGameControlAble.h"

USING_NS_CC;

void MagiciteGameControlAble::dispatchKeyPress(EventKeyboard::KeyCode keyCode, Event* event, MagiciteGameControlAble *controlable)
{
    controlable->onKeyPressed(keyCode, event);
}

void MagiciteGameControlAble::dispatchKeyRelease(EventKeyboard::KeyCode keyCode, Event* event, MagiciteGameControlAble *controlable)
{
    controlable->onKeyReleased(keyCode, event);
}
