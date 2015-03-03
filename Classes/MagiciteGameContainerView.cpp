#include "MagiciteGameContainerView.h"
#include "MagiciteItemContainer.h"
#include "MagiciteItem.h"
#include "MagiciteEffectItem.h"

USING_NS_CC;

MagiciteGameContainerView::MagiciteGameContainerView()
{
}

MagiciteGameContainerView::~MagiciteGameContainerView()
{
    CC_SAFE_DELETE(_container);
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
    _list = new std::vector<MagiciteGameObject*>(max_size);
    _container = new MagiciteItemContainer(max_size);

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
    auto item = _container->getItem(n);
    if (item != nullptr)
    {
        if (item->_itemType == MagiciteItem::EffectItem)
        {
            reinterpret_cast<MagiciteEffectItem*>(item)->positive(_obj);
        }
    }
}
