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

bool MagiciteGameContainerView::init(MagiciteGameObject* obj, int max_size)
{
    if (!MagiciteGameObject::init())
    {
        return false;
    }

    _max_size = max_size;
    _obj = obj;
    _list = new std::vector<std::pair<int, MagiciteItem*>>(max_size);

    return true;
}

void MagiciteGameContainerView::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{

}

void MagiciteGameContainerView::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{

}

void MagiciteGameContainerView::ItemEvent(int n)
{
    auto iter = _list->at(n);
    auto item = iter.second;

    if (item != nullptr)
    {
        if (item->_itemType == MagiciteItem::EffectItem)
        {
            reinterpret_cast<MagiciteEffectItem*>(item)->positive(_obj);
        }
    }
}
