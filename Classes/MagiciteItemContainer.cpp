#include "MagiciteItemContainer.h"
#include "MagiciteItem.h"
#include "MagiciteGameContainerView.h"

USING_NS_CC;

MagiciteItemContainer::MagiciteItemContainer()
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
    auto iter = std::find_if(_container.begin(), _container.end(), [id](const std::pair<int, MagiciteItem*>& x)->bool{
        return x.first == id;
    });
    if (iter != _container.end())
    {
        return iter->second;
    }
    return nullptr;
}

void MagiciteItemContainer::bindView(MagiciteGameContainerView* view)
{
    _view = view;
}