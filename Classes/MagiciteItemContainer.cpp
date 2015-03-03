#include "MagiciteItemContainer.h"
#include "MagiciteItem.h"
#include "MagiciteGameContainerView.h"
#include "MagiciteEffectItem.h"

USING_NS_CC;

MagiciteItemContainer::MagiciteItemContainer(MagiciteGameObject* obj)
:_obj(obj)
{

}

MagiciteItemContainer::~MagiciteItemContainer()
{

}

void MagiciteItemContainer::addItem(MagiciteItem* item)
{
    _container.push_back(std::make_pair(item->getItemId(), item));
    if (_view != nullptr)
    {
        _view->addItem(item->getItemObject());
    }
}

void MagiciteItemContainer::eraseItem(int id)
{
    auto iter = std::find_if(_container.begin(), _container.end(), [id](const std::pair<int, MagiciteItem*>& x)->bool{
            return x.first == id;
    });
    if (iter != _container.end())
    {
        _container.erase(iter);
    }
}

MagiciteItem* MagiciteItemContainer::getItem(int id)
{
    if (std::size_t(id) < _container.size())
    {
        auto item = _container[id];
        return item.second;
    }
    return nullptr;
}

void MagiciteItemContainer::bindView(MagiciteGameContainerView* view)
{
    _view = view;
    _view->_touch_event = std::bind(&MagiciteItemContainer::touchEvent, this, std::placeholders::_1);
}

void MagiciteItemContainer::touchEvent(int n)
{
    auto item = getItem(n);
    if (item != nullptr)
    {
        if (item->_itemType == MagiciteItem::EffectItem)
        {
            reinterpret_cast<MagiciteEffectItem*>(item)->positive(_obj);
        }
    }
}