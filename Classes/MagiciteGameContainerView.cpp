#include "MagiciteGameContainerView.h"
#include "MagiciteItem.h"
#include "MagiciteEffectItem.h"

USING_NS_CC;

MagiciteGameContainerView::MagiciteGameContainerView()
{
}

MagiciteGameContainerView::~MagiciteGameContainerView()
{
    CC_SAFE_DELETE(_list);
}

bool MagiciteGameContainerView::init(int max_size)
{
    if (!MagiciteGameObject::init())
    {
        return false;
    }

    _max_size = max_size;
    _list = new std::vector<std::pair<int, MagiciteItem*>>(max_size);

    return true;
}

MagiciteItem* MagiciteGameContainerView::getItem(int num)
{
    return _list->at(num).second;
}

void MagiciteGameContainerView::setViewInvisible(bool is_visible)
{
    this->setVisible(is_visible);
}

bool MagiciteGameContainerView::getViewInvisible() const
{
    return this->isVisible();
}

void MagiciteGameContainerView::addItem(MagiciteItem* item, std::vector<std::pair<int, MagiciteItem*>>::iterator iter)
{
    iter->first = item->getItemId();
    iter->second = item;
}

void MagiciteGameContainerView::eraseItem(std::vector<std::pair<int, MagiciteItem*>>::iterator iter)
{
    iter->first = 0;
    iter->second = nullptr;
}

void MagiciteGameContainerView::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_0:
        _itemEvent(9);
        break;
    case EventKeyboard::KeyCode::KEY_1:
        _itemEvent(0);
        break;
    case EventKeyboard::KeyCode::KEY_2:
        _itemEvent(1);
        break;
    case EventKeyboard::KeyCode::KEY_3:
        _itemEvent(2);
        break;
    case EventKeyboard::KeyCode::KEY_4:
        _itemEvent(3);
        break;
    case EventKeyboard::KeyCode::KEY_5:
        _itemEvent(4);
        break;
    case EventKeyboard::KeyCode::KEY_6:
        _itemEvent(5);
        break;
    case EventKeyboard::KeyCode::KEY_7:
        _itemEvent(6);
        break;
    case EventKeyboard::KeyCode::KEY_8:
        _itemEvent(7);
        break;
    case EventKeyboard::KeyCode::KEY_9:
        _itemEvent(8);
        break;
    default:
        break;
    }
}

void MagiciteGameContainerView::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{

}