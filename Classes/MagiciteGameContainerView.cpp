#include "MagiciteGameContainerView.h"

USING_NS_CC;

MagiciteGameContainerView::MagiciteGameContainerView(int n/* = _max_size*/)
:_list(n)
{

}

MagiciteGameContainerView::~MagiciteGameContainerView()
{

}

bool MagiciteGameContainerView::init()
{
    if (!MagiciteGameObject::init())
    {
        return false;
    }

    return true;
}

void MagiciteGameContainerView::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{

}

void MagiciteGameContainerView::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{

}