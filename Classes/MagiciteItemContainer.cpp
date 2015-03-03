#include "MagiciteItemContainer.h"
#include "MagiciteItem.h"
#include "MagiciteGameContainerView.h"
#include "MagiciteEffectItem.h"

USING_NS_CC;

MagiciteItemContainer::MagiciteItemContainer(int max_size)
:_max_size(max_size), _container(max_size)
{

}

MagiciteItemContainer::~MagiciteItemContainer()
{

}

void MagiciteItemContainer::addItem(MagiciteItem* item)
{
    auto iter = std::find_if(_container.begin(), _container.end(), [](const std::pair<int, MagiciteItem*>& x)->bool{
        return x.second == nullptr;
    });
    if (iter != _container.end())
    {
        *iter = std::make_pair(item->getItemId(), item);
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

MagiciteItem* MagiciteItemContainer::getItem(int index)
{
    if (std::size_t(index) < _container.size())
    {
        auto item = _container[index];
        return item.second;
    }
    return nullptr;
}

